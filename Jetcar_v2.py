import smbus2
import time
from inputs import get_gamepad
import math
import threading

class JetCar:
    def __init__(self, servo_addr=0x40, motor_addr=0x60):
        # Servo setup
        self.servo_bus = smbus2.SMBus(1)
        self.SERVO_ADDR = servo_addr
        self.STEERING_CHANNEL = 0
        
        # Servo config
        self.MAX_ANGLE = 180
        self.SERVO_CENTER_PWM = 330 + 0
        self.SERVO_LEFT_PWM = 330 - 250
        self.SERVO_RIGHT_PWM = 330 + 250
        
        # Motor controller setup
        self.motor_bus = smbus2.SMBus(1)
        self.MOTOR_ADDR = motor_addr
        
        # Control flags
        self.running = False
        self.current_speed = 0
        self.current_angle = 0
        #find /usr/include -name i2c-dev.h
        # Initialize both systems
        self.init_servo()
        self.init_motors()
        
    def init_servo(self):
        try:
            # Reset PCA9685
            self.servo_bus.write_byte_data(self.SERVO_ADDR, 0x00, 0x06)
            time.sleep(0.1)
            
            # Setup servo control
            self.servo_bus.write_byte_data(self.SERVO_ADDR, 0x00, 0x10)
            time.sleep(0.1)
            
            # Set frequency (~50Hz)
            self.servo_bus.write_byte_data(self.SERVO_ADDR, 0xFE, 0x79)
            time.sleep(0.1)
            
            # Configure MODE2
            self.servo_bus.write_byte_data(self.SERVO_ADDR, 0x01, 0x04)
            time.sleep(0.1)
            
            # Enable auto-increment
            self.servo_bus.write_byte_data(self.SERVO_ADDR, 0x00, 0x20)
            time.sleep(0.1)
            
            return True
        except Exception as e:
            print(f"Servo init error: {e}")
            return False

    def init_motors(self):
        try:
            # Configure motor controller
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x00, 0x20)
            
            # Set frequency to 60Hz
            prescale = int(math.floor(25000000.0 / 4096.0 / 100 - 1))
            oldmode = self.motor_bus.read_byte_data(self.MOTOR_ADDR, 0x00)
            newmode = (oldmode & 0x7F) | 0x10
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x00, newmode)
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0xFE, prescale)
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x00, oldmode)
            time.sleep(0.005)
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x00, oldmode | 0xa1)
            
            return True
        except Exception as e:
            print(f"Motor init error: {e}")
            return False


    def set_steering(self, angle):
        """Set steering angle (-90 to +90 degrees)"""
        angle = max(-self.MAX_ANGLE, min(self.MAX_ANGLE, angle))
        
        if angle < 0:
            pwm = int(self.SERVO_CENTER_PWM + 
                     (angle / self.MAX_ANGLE) * (self.SERVO_CENTER_PWM - self.SERVO_LEFT_PWM))
        elif angle > 0:
            pwm = int(self.SERVO_CENTER_PWM + 
                     (angle / self.MAX_ANGLE) * (self.SERVO_RIGHT_PWM - self.SERVO_CENTER_PWM))
        else:
            pwm = self.SERVO_CENTER_PWM
            
        self.set_servo_pwm(self.STEERING_CHANNEL, 0, pwm)
        self.current_angle = angle

    def set_angle(self, angle):
        self.set_servo_pwm(self.STEERING_CHANNEL, 0, angle)

    def angle_to_pwm(self, angle):
        """
        Converte ângulo (-90 a +90) para valor PWM
        Ângulo negativo = esquerda
        Ângulo positivo = direita
        Ângulo zero = centro
        """
        # Limita o ângulo entre -90 e +90
        angle = max(-self.MAX_ANGLE, min(self.MAX_ANGLE, angle))
        
        if angle < 0:  # Esquerda
            # Interpola entre centro e esquerda
            return int(self.SERVO_CENTER_PWM + 
                      (angle / self.MAX_ANGLE) * (self.SERVO_CENTER_PWM - self.SERVO_LEFT_PWM))
        elif angle > 0:  # Direita
            # Interpola entre centro e direita
            return int(self.SERVO_CENTER_PWM + 
                      (angle / self.MAX_ANGLE) * (self.SERVO_RIGHT_PWM - self.SERVO_CENTER_PWM))
        else:  # Centro
            return self.SERVO_CENTER_PWM

   # def set_angle(self, angle):
   #     """
   #     Define o ângulo do servo (-180 a +180 graus)
   #     Negativo = Esquerda
   #     Positivo = Direita
   #     Zero = Centro
   #     """
   #     if not isinstance(angle, (int, float)):
   #         print("Ângulo deve ser um número")
   #         return False
   #         
   #     if abs(angle) > self.MAX_ANGLE:
   #         print(f"Ângulo deve estar entre -{self.MAX_ANGLE} e +{self.MAX_ANGLE} graus")
   #         return False
   #     
   #     direction = "centro" if angle == 0 else "esquerda" if angle < 0 else "direita"
   #     print(f"Movendo servo para {abs(angle)}° ({direction})")
   #     
   #     pwm_value = self.angle_to_pwm(angle)
   #     return self.set_pwm(self.STEERING_CHANNEL, 0, pwm_value)
#
    def set_servo_pwm(self, channel, on_value, off_value):
        """Set PWM values for servo"""
        try:
            base_reg = 0x06 + (channel * 4)
            self.servo_bus.write_byte_data(self.SERVO_ADDR, base_reg, on_value & 0xFF)
            self.servo_bus.write_byte_data(self.SERVO_ADDR, base_reg + 1, on_value >> 8)
            self.servo_bus.write_byte_data(self.SERVO_ADDR, base_reg + 2, off_value & 0xFF)
            self.servo_bus.write_byte_data(self.SERVO_ADDR, base_reg + 3, off_value >> 8)
            return True
        except Exception as e:
            print(f"Servo PWM error: {e}")
            return False

    def set_motor_pwm(self, channel, value):
        """Set PWM value for motor channel"""
        value = min(max(value, 0), 4095)
        try:
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x06 + 4 * channel, 0)
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x07 + 4 * channel, 0)
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x08 + 4 * channel, value & 0xFF)
            self.motor_bus.write_byte_data(self.MOTOR_ADDR, 0x09 + 4 * channel, value >> 8)
        except Exception as e:
            print(f"Motor PWM error: {e}")

    def set_speed(self, speed):
        """Set motor speed (-100 to +100)"""
        speed = max(-100, min(100, speed))
        pwm_value = int(abs(speed) / 100.0 * 4095)
        
        if speed > 0:  # Forward
            self.set_motor_pwm(0, pwm_value)  # IN1
            self.set_motor_pwm(1, 0)          # IN2
            self.set_motor_pwm(2, pwm_value)  # ENA
            self.set_motor_pwm(5, pwm_value)  # IN3
            self.set_motor_pwm(6, 0)          # IN4
            self.set_motor_pwm(7, pwm_value)  # ENB
        elif speed < 0:  # Backward
            self.set_motor_pwm(0, pwm_value)  # IN1
            self.set_motor_pwm(1, pwm_value)  # IN2
            self.set_motor_pwm(2, 0)          # ENA
            self.set_motor_pwm(6, pwm_value)  # IN3
            self.set_motor_pwm(7, pwm_value)  # IN4
            self.set_motor_pwm(8, 0)          # ENB
        else:  # Stop
            for channel in range(9):
                self.set_motor_pwm(channel, 0)
        
        self.current_speed = speed

    def process_joystick(self):
        print("Gamepad control started")
        print("Left stick: steering")
        print("RT: forward, LT: reverse")
        print("START/SELECT: exit")
        
        while self.running:
            try:
                events = get_gamepad()
                for event in events:
                    if event.code == 'ABS_X':
                        current_angle = ((event.state - 127) / 127) * 100
                        self.set_steering(current_angle)
                    elif event.code == 'ABS_RZ':
                        # Map 0-255 to -100 to +100
                        # 0-127 = reverse
                        # 128 = stop
                        # 129-255 = forward
                        if event.state == 128:
                            self.current_speed = 0
                        elif event.state < 128:
                            self.current_speed = (128 - event.state) / 128.0 * 100
                        else:
                            self.current_speed = -(event.state - 128) / 127.0 * 100
                        self.set_speed(self.current_speed)
                    elif event.code == 'ABS_BRAKE':
                        self.current_speed = -event.state / 255.0 * 100
                        self.set_speed(self.current_speed)
                    elif event.code in ['BTN_START', 'BTN_SELECT'] and event.state == 1:
                        self.running = False
                        break
            except KeyboardInterrupt:
                self.running = False
                break
            except Exception as e:
                print(f"Gamepad error: {e}")
                continue

    def start(self):
        """Start the car control"""
        self.running = True
        self.joystick_thread = threading.Thread(target=self.process_joystick)
        self.joystick_thread.start()

    def stop(self):
        """Stop the car and cleanup"""
        self.running = False
        if hasattr(self, 'joystick_thread'):
            self.joystick_thread.join()
        self.set_speed(0)
        self.set_steering(0)
        self.servo_bus.close()
        self.motor_bus.close()


try:
    car = JetCar()
    car.start()
    while car.running:
        time.sleep(0.5)
except Exception as e:
    print(f"Error: {e}")
    car.stop()
    exit(1)
    
car.stop()