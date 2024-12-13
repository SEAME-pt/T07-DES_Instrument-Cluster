#include <CAN.h>

const int ENCODER_PIN = 2;      // Pino conectado ao sensor de velocidade
volatile unsigned long pulseCount = 0;
unsigned long lastTime = 0;
unsigned int speed = 0;         // Velocidade calculada

// Interrupção chamada a cada pulso do sensor
void pulseISR() {
    pulseCount++;
}

void setup() {
    pinMode(ENCODER_PIN, INPUT_PULLUP); // Configura o pino do sensor
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), pulseISR, RISING); // Configura interrupção

    Serial.begin(9600);

    // Inicializa o barramento CAN a 500 kbps
    if (!CAN.begin(500E3)) {
        Serial.println("CAN BUS Initialization Failed");
        while (1); // Trava o programa caso falhe
    }

    Serial.println("CAN BUS Initialized");
}

void loop() {
    unsigned long currentTime = millis();

    // Calcula a velocidade a cada segundo
    if (currentTime - lastTime >= 1000) {
        speed = pulseCount; // Assume 1 pulso = 1 RPM
        pulseCount = 0;     // Reinicia a contagem de pulsos
        lastTime = currentTime;

        // Envia a velocidade pelo CAN
        CAN.beginPacket(0x100);                 // Define o ID do pacote CAN
        CAN.write((speed >> 8) & 0xFF);         // Byte mais significativo
        CAN.write(speed & 0xFF);               // Byte menos significativo
        CAN.endPacket();                       // Finaliza o envio

        // Exibe a velocidade no monitor serial
        Serial.print("Speed: ");
        Serial.println(speed);
    }
}
