#include <L293D.h>

L293D motorDriver(4, 5, 6, 7); // IN1-4 pins

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    switch (cmd) {
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      default: stop(); break;
    }
  }
}

void forward() { motorDriver.forward(); }
void backward() { motorDriver.backward(); }
void left() { motorDriver.turnLeft(); }
void right() { motorDriver.turnRight(); }
void stop() { motorDriver.stop(); }