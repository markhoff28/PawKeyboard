/*
Emergency ALT-F4 Button V1.0
for Arduino Pro Micro
https://www.printables.com/model/1251991-emergency-alt-f4-button
*/

#include <Keyboard.h>

const byte buttonPin = 7;
const byte GNDpin = 8;

bool buttonState;
bool lastButtonState;

const int holdDuration = 10000;
unsigned long buttonPressTime;

bool shutdownDone = true;
bool enableSerial = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(GNDpin, OUTPUT);
  digitalWrite(GNDpin, LOW);

  if (digitalRead(buttonPin) == LOW) {
    enableSerial = true;
    Serial.begin(9600);
  }

  Keyboard.begin();

  delay(1000);
}

void loop() {

  buttonState = digitalRead(buttonPin);
  if (enableSerial == true) {
    Serial.print("ButtonState: ");
    Serial.print(buttonState);
    Serial.print(" | counter: ");
  }
  if (buttonState == LOW) {
    if (enableSerial == true) {
      Serial.print(millis() - buttonPressTime);
    }
  }
  if (enableSerial == true) {
    Serial.println();
  }

  if (lastButtonState == LOW && buttonState == HIGH) {  //detect rising edge
    if (shutdownDone == false) {
      unsigned long pressDuration = millis() - buttonPressTime;
      SEND_FURRY_ASCII(pressDuration);
    }
  }

  if (lastButtonState == HIGH && buttonState == LOW) {  //detect falling edge
    buttonPressTime = millis();                         //capture millis when button is pressed down
    shutdownDone = false;                               //reset shutdown state
  }

  lastButtonState = buttonState;
  delay(20);
}

void SEND_FURRY_ASCII(unsigned long duration) {
  if (duration < 1000) {
    Keyboard.print("x3 ");
  } else if (duration < 2000) {
    Keyboard.print("O3 ");
  } else if (duration < 3000) {
    Keyboard.print("owo ");
  } else if (duration < 4000) {
    Keyboard.print("ฅ^•ﻌ•^ฅ ");
  } else if (duration < 5000) {
    Keyboard.print("Paw ");
  } else {
    Keyboard.print("pawsies! x3");
  }
}
