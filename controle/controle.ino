#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

int ledPin = 10;
int leftButton = 7;
int rightButton = 6;

RH_ASK driver;

void setup()
{
    Serial.begin(115200); // Debugging only
    pinMode(ledPin, OUTPUT);
    pinMode(leftButton, INPUT_PULLUP);
    pinMode(rightButton, INPUT_PULLUP);
    if (!driver.init())
        Serial.println("init failed");
}

void loop()
{
    if (digitalRead(leftButton) == LOW)
    {
        digitalWrite(ledPin, HIGH);
        driver.send((uint8_t *)"l", 1);
        driver.waitPacketSent();
        delay(100);
        digitalWrite(ledPin, LOW);
    }
    if (digitalRead(rightButton) == LOW)
    {
        digitalWrite(ledPin, HIGH);
        driver.send((uint8_t *)"r", 1);
        driver.waitPacketSent();
        delay(100);
        digitalWrite(ledPin, LOW);
    }
}
