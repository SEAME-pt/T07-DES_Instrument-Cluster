import Jetson.GPIO as GPIO
import time


#https://developer.ridgerun.com/wiki/index.php/How_to_test_GPIO_with_Jetson_GPIO_Library#Example

SPEED_SENSOR_PIN = 18  # Pin GPIO 18

GPIO.setmode(GPIO.BOARD)
GPIO.setup(SPEED_SENSOR_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Resistor pull-up

count = 0
last_time = None
intervals = []

try:
    while True:
        if GPIO.input(SPEED_SENSOR_PIN) == GPIO.LOW:
            current_time = time.time()
            
            while GPIO.input(SPEED_SENSOR_PIN) == GPIO.LOW:
                time.sleep(0.01)

            count += 1
            print(f"press: {count}")

            if last_time is not None:
                interval = current_time - last_time
                intervals.append(interval)
                print(f"Interval: {interval:.2f} secs")

            last_time = current_time

        if len(intervals) > 0:
            avg_interval = sum(intervals) / len(intervals)
            speed = 1 / avg_interval if avg_interval > 0 else 0
            print(f"velocity: {speed:.2f} km/h")
        
        time.sleep(0.1)

finally:
    GPIO.cleanup()
    print("GPIO out!")

