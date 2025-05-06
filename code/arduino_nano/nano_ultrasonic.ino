#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// NRF24L01 radio setup
RF24 radio(9, 8); // CE, CSN
const byte address[6] = "00001";

// Motor control pins
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

// Ultrasonic sensor pins
const int trigPin = 3;
const int echoPin = 2;

// Variables
float duration, distance;
String voiceCommand = "";

// Setup function
void setup() {
  // Initialize motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialize ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Begin serial and radio communication
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.startListening();
}

// Main loop
