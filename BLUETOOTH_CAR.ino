#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

// Motor Pins
#define ENA 13
#define IN1 14
#define IN2 27
#define IN3 26
#define IN4 25
#define ENB 12

int speedValue = 255;  // Speed: 0 - 255

void setup() {
  Serial.begin(115200);
  SerialBT.begin("bl car "); // Bluetooth name

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopMotors();
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    Serial.println(command);

    switch (command) {
      case 'F': moveForward(); break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft(); break;
      case 'R': turnRight(); break;
      case 'S': stopMotors(); break;
    }
  }
}

void moveForward() {
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  digitalWrite(IN1, HIGH); // Left motors forward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); // Right motors forward
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  digitalWrite(IN1, LOW);  // Left motors backward
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  // Right motors backward
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  digitalWrite(IN1, LOW);   // Left backward
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);  // Right forward
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);

  digitalWrite(IN1, HIGH);  // Left forward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);   // Right backward
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
