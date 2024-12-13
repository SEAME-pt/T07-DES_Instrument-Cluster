#include <SPI.h>
#include "mcp2515_can.h"  // Biblioteca para o MCP2515 CAN-Bus Shield

#define CAN_2515
const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;

mcp2515_can CAN(SPI_CS_PIN);

const int ENCODER_PIN = 3;
volatile unsigned long pulseCount = 0;
unsigned long lastTime = 0;
unsigned int speed = 0;
const unsigned int pulsesPerRevolution = 36;

// Interrupção chamada a cada pulso do sensor
void pulseISR() {
    pulseCount++;
}

void setup() {
    pinMode(ENCODER_PIN, INPUT_PULLUP); // config event for pin 3
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), pulseISR, RISING); // config the interrupt on pin 3

    Serial.begin(9600);

    // Inicializar CAN-Bus Shield
    if (CAN.begin(CAN_500KBPS) == CAN_OK) {
        Serial.println("CAN BUS Initialized");
    } else {
        Serial.println("CAN BUS Initialization Failed");
        while (1);  // wait until connect
    }
}

void loop() {
    unsigned long currentTime = millis();

    if (currentTime - lastTime >= 1000) {
        noInterrupts();
        unsigned long count = pulseCount;
        pulseCount = 0;
        interrupts();

        speed = (count / pulsesPerRevolution) * 0.215 * 3600; // m/h

        byte message[2];
        message[0] = (speed >> 8) & 0xFF;  // Byte high
        message[1] = speed & 0xFF;         // Byte low
        Serial.println(speed);
        Serial.print("high: ");
        Serial.println(message[0]);
        Serial.print("low: ");
        Serial.println(message[1]);
        CAN.sendMsgBuf(0x100, 0, 2, message);

        lastTime = currentTime;
    }
}
