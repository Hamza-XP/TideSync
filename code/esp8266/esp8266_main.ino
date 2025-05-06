#include <SoftwareSerial.h>
#include <VoiceRecognitionV2.h>
#include <nRF24L01.h>
#include <RF24.h>

// Voice Recognition
VR myVR(2, 3); // RX, TX pins
#define forwardCommand 0
#define backwardCommand 1
#define leftCommand 2
#define rightCommand 3

// nRF24L01 Radio
RF24 radio(4, 5); // CE, CSN
const byte address[6] = "00001";

// Motor Control Pins (Arduino Uno)
SoftwareSerial unoSerial(6, 7); // RX, TX to Uno

void setup() {
  Serial.begin(9600);
  myVR.begin(9600);
  unoSerial.begin(9600);
  
  // Initialize nRF24L01
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  
  // Load Voice Commands
  myVR.load((uint8_t)forwardCommand);
  myVR.load((uint8_t)backwardCommand);
  myVR.load((uint8_t)leftCommand);
  myVR.load((uint8_t)rightCommand);
}

void loop() {
  // Check for voice commands
  int command = myVR.recognize();
  if (command >= 0) {
    sendCommand(command);
  }

  // Check for Bluetooth/Wi-Fi app commands
  if (Serial.available()) {
    String appCommand = Serial.readString();
    sendCommand(appCommand);
  }
}

void sendCommand(int cmd) {
  switch (cmd) {
    case forwardCommand:
      radio.write("F", 1); // Fallback radio
      unoSerial.write("F"); // Send to Arduino Uno
      break;
    case backwardCommand:
      radio.write("B", 1);
      unoSerial.write("B");
      break;
    case leftCommand:
      radio.write("L", 1);
      unoSerial.write("L");
      break;
    case rightCommand:
      radio.write("R", 1);
      unoSerial.write("R");
      break;
  }
}