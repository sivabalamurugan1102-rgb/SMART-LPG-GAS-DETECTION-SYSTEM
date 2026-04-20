#include <Servo.h>

Servo myServo;

int gasSensor = A0;     // MQ-6 analog pin
int buzzer = 8;         // Buzzer pin
int relay = 7;          // Relay (fan) pin
int threshold = 300;    // Gas limit (adjust based on testing)

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  myServo.attach(9);   // Servo pin

  Serial.begin(9600);

  digitalWrite(buzzer, LOW);
  digitalWrite(relay, LOW);
  myServo.write(0);    // Valve open position
}

void loop() {
  int gasValue = analogRead(gasSensor);
  Serial.println(gasValue);

  if (gasValue > threshold) {
    // GAS LEAK DETECTED
    digitalWrite(buzzer, HIGH);   // Beep sound
    digitalWrite(relay, HIGH);    // Fan ON
    myServo.write(90);            // Close gas valve

    Serial.println("Gas Leakage Detected!");
  } 
  else {
    // NORMAL CONDITION
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, LOW);
    myServo.write(0);             // Open valve

    Serial.println("Normal");
  }

  delay(1000);
}
