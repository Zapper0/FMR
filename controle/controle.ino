#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

int ledPin = 10;
int leftButton = 7;
int rightButton = 6;

RH_ASK driver; // init radio driver

void setup()
{
    Serial.begin(115200);

    pinMode(ledPin, OUTPUT);
    pinMode(leftButton, INPUT_PULLUP);
    pinMode(rightButton, INPUT_PULLUP);

    if (!driver.init())
        Serial.println("init failed"); // Make sure radio is working
}
void send_message(char * msg)
{
    digitalWrite(ledPin, HIGH); // Turn on a light to show transmitting

    driver.send((uint8_t *)msg, 1); // Send a message
    driver.waitPacketSent();        // Wait for message to be sent
    
    while (digitalRead(leftButton) == LOW) // Await while button is pressed
        digitalWrite(ledPin, HIGH);

    driver.send((uint8_t *)NULL, 1); // Send null message
    driver.waitPacketSent();         // Wait for message to be sent

    digitalWrite(ledPin, LOW); // Turn off the light to show end of transmission   
}
void loop()
{
    int left = digitalRead(leftButton); //save the readings
    int right = digitalRead(rightButton);
    if (left || right)
    {
        delay(10);
        if (left && right) ? send_message("f") // compare the values and send messages
        : (left) ? send_message("l") 
        : (right) ? send_message("r") : send_message(NULL);
    }
}
