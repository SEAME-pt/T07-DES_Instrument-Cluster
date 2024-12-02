### **Project Title:**
**CAN Interface Between Arduino Uno R3 and Raspberry Pi 4B for Real-Time Speed Measurement**

---

### **Project Description:**
This project involves using an Arduino Uno R3 to process speed data from a pulse encoder (e.g., SEN-Speed sensor) and transmitting the data to a Raspberry Pi 4B over a CAN bus. The Raspberry Pi retrieves the speed value and displays it on its standard output (STDOUT). The system simulates an automotive application where a speed sensor communicates with a central controller using CAN. All code is implemented in C++.

---

### **Learning Objectives:**

1. Learn to interface a pulse encoder with an Arduino Uno and process speed data.
2. Understand and implement CAN communication between Arduino and Raspberry Pi.
3. Develop a C++ application for data acquisition and communication.
4. Gain practical experience with embedded systems and real-time communication.

---

### **System Design:**

1. **Hardware Components:**
   - Arduino Uno R3.
   - SEN-Speed sensor.
   - MCP2515 CAN transceiver module (one for each device).
   - Raspberry Pi 4B.
   - Jumper wires and 120-ohm termination resistors.

2. **System Architecture:**
   - **Arduino Uno:** Reads pulse data from the SEN-Speed sensor, calculates the speed, and sends the speed value as a CAN message.
   - **Raspberry Pi 4B:** Retrieves the speed value over CAN and displays it on the terminal.

---

### **Implementation Steps:**

#### **Step 1: Set Up the Arduino Uno**

1. **Connect the SEN-Speed Sensor:**
   - Connect the sensor's signal wire to a digital pin (e.g., D2) of the Arduino Uno.
   - Power the sensor (5V) and connect the ground.

2. **Connect the MCP2515 CAN Module:**
   - **MCP2515 to Arduino Wiring:**

     | MCP2515 Pin | Arduino Pin |
     |-------------|-------------|
     | VCC         | 5V          |
     | GND         | GND         |
     | SCK         | D13         |
     | SI          | D11         |
     | SO          | D12         |
     | CS          | D10         |

3. **Write the Arduino C++ Code:**
   - Use the **MCP_CAN** library for CAN communication.
   - Configure the interrupt on the encoder pin to count pulses.
   - Calculate the speed based on pulses over a fixed interval.
   - Send the speed value as a CAN message.

   **Arduino Code (C++):**
   ```cpp
   #include <SPI.h>
   #include <mcp_can.h>

   const int SPI_CS_PIN = 10;
   const int ENCODER_PIN = 2; // Pin connected to the SEN-Speed sensor
   volatile unsigned long pulseCount = 0;
   unsigned long lastTime = 0;
   unsigned int speed = 0;

   MCP_CAN CAN(SPI_CS_PIN);

   void IRAM_ATTR pulseISR() {
       pulseCount++;
   }

   void setup() {
       pinMode(ENCODER_PIN, INPUT_PULLUP);
       attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), pulseISR, RISING);

       Serial.begin(115200);
       if (CAN.begin(MCP_ANY, 500000, SPI_CS_PIN) == CAN_OK) {
           Serial.println("CAN BUS Initialized");
       } else {
           Serial.println("CAN BUS Initialization Failed");
           while (1);
       }
       CAN.setMode(MCP_NORMAL);
   }

   void loop() {
       unsigned long currentTime = millis();
       if (currentTime - lastTime >= 1000) { // Calculate speed every second
           speed = pulseCount; // Assuming 1 pulse = 1 RPM
           pulseCount = 0;
           lastTime = currentTime;

           // Send speed over CAN
           byte data[2] = { highByte(speed), lowByte(speed) };
           CAN.sendMsgBuf(0x100, 0, 2, data);

           Serial.print("Speed: ");
           Serial.println(speed);
       }
   }
   ```

---

#### **Step 2: Set Up the Raspberry Pi**

1. **Connect the MCP2515 CAN Module:**
   - **MCP2515 to Raspberry Pi Wiring:**

     | MCP2515 Pin | Raspberry Pi Pin |
     |-------------|------------------|
     | VCC         | 3.3V (Pin 1 or 17) |
     | GND         | GND (Pin 6 or 9) |
     | SCK         | GPIO11 (Pin 23) |
     | SI          | GPIO10 (Pin 19) |
     | SO          | GPIO9 (Pin 21)  |
     | CS          | GPIO8 (Pin 24)  |
     | INT         | GPIO25 (Pin 22) |

2. **Enable SPI and Install CAN Utilities:**
   - Enable SPI using `raspi-config`.
   - Install the necessary tools:
     ```bash
     sudo apt update
     sudo apt install can-utils
     ```

3. **Write the Raspberry Pi C++ Code:**
   - Use the `socketcan` API to read CAN messages.
   - Display the speed value on the terminal.

   **Raspberry Pi Code (C++):**
   ```cpp
   #include <iostream>
   #include <cstring>
   #include <linux/can.h>
   #include <linux/can/raw.h>
   #include <sys/socket.h>
   #include <net/if.h>
   #include <unistd.h>

   int main() {
       struct sockaddr_can addr;
       struct ifreq ifr;
       struct can_frame frame;

       int sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
       if (sock < 0) {
           perror("Socket");
           return 1;
       }

       strcpy(ifr.ifr_name, "can0");
       ioctl(sock, SIOCGIFINDEX, &ifr);

       addr.can_family = AF_CAN;
       addr.can_ifindex = ifr.ifr_ifindex;

       if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
           perror("Bind");
           return 1;
       }

       while (true) {
           int nbytes = read(sock, &frame, sizeof(struct can_frame));
           if (nbytes > 0 && frame.can_id == 0x100) {
               int speed = (frame.data[0] << 8) | frame.data[1];
               std::cout << "Speed: " << speed << " RPM" << std::endl;
           }
       }

       close(sock);
       return 0;
   }
   ```

---

#### **Step 3: Testing and Debugging**

1. **Bring up the CAN Interface on Raspberry Pi:**
   ```bash
   sudo ip link set can0 up type can bitrate 500000
   ```

2. **Run the Arduino and Raspberry Pi Code:**
   - Upload the Arduino code to the Uno.
   - Compile and run the Raspberry Pi C++ code.

3. **Verify Communication:**
   - Check the Raspberry Pi terminal for real-time speed values.

---

### **Extensions:**

1. **Error Handling:**
   Add CRC checks or error-handling mechanisms for corrupted CAN messages.

2. **Visualization:**
   Use an external display connected to the Raspberry Pi to show the speed visually.

3. **Multi-Sensor Integration:**
   Add more sensors to the Arduino and send their data via CAN.

---

Labels: embedded systems, communication protocols, and real-time data processing. 