#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

int ledPin = 12;
int lMotor = 7;
int rMotor = 8;

RH_ASK driver;

void setup()
{
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(lMotor, OUTPUT);
  pinMode(rMotor, OUTPUT);

  // Set relays off
  digitalWrite(lMotor, HIGH);
  digitalWrite(rMotor, HIGH);

  if (!driver.init())
    Serial.println("init failed"); // Make sure radio is working
}

void loop()
{
  uint8_t buf[1];
  uint8_t buflen = sizeof(buf);

  // blink the led when a message is received
  if (driver.recv(buf, &buflen)) // Check if received packet is correct size
  {
    int i;
    // Message with a good checksum received, proceed

    // Blink led
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);

    // Print received message (debug)
    Serial.print((char *)buf);
    Serial.print(" | ");
    Serial.print(String((char *)buf == "l"));
    Serial.print(" | ");
    Serial.println(strcmp((char *)buf, "r"));
  }
}
