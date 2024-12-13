#include <CAN.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  Serial.println("CAN Receiver");
}

void loop() {
  int packetSize = CAN.parsePacket();

  if (packetSize) {
    if (!CAN.packetRtr()) {
      if (packetSize == 2) { // wait for 2 bytes
        // read and join the 2 bytes
        int speed = (CAN.read() << 8) | CAN.read();
        
        Serial.print(speed);
        Serial.println(" km/h");
      } else {
        Serial.println("Unexpected packet size");
      }
    }
  }
}

