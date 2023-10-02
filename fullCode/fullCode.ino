#include <Servo.h>

Servo servo;          // Create a Servo object
int servoPin = 9;     // Define the base servo signal pin
int initialPosition = 90; // Initial position in degrees
int targetPosition = 90;  // Target position in degrees
int step = 1;          // Step size for each movement
int delayTime = 15;    // Delay time in milliseconds between each step


int posF=20; //drop position
int posI=80; //dump pos

Servo s;
int sPin=8; //girane wala servo

void setup() {
  servo.attach(servoPin);     // Attaches the servo to the specified pin (pin 9)
  servo.write(initialPosition); // Set the initial position
  Serial.begin(9600);         // Initialize serial communication

  s.attach(sPin);
  s.write(posI);
  
}

void loop() {
  while(Serial.available()==0){

  }
  if (Serial.available() > 0) {
    int userInput = Serial.parseInt(); // Read the user input as an integer

    // Check if the input is valid (1, 2, 3, or 4)
    if (userInput >= 1 && userInput <= 4) {
      switch (userInput) {
        case 1: // Target angle: 20 degrees
          targetPosition = 20;
          break;
        case 2: // Target angle: 70 degrees
          targetPosition = 70;
          break;
        case 3: // Target angle: 130 degrees
          targetPosition = 140;
          break;
        case 4: // Target angle: 180 degrees
          targetPosition = 180;
          break;
      }

      // Move the servo to the target position
      if (servo.read() < targetPosition) {
        for (int pos = servo.read(); pos <= targetPosition; pos += step) {
          servo.write(pos);
          delay(delayTime);
        }
      } else if (servo.read() > targetPosition) {
        for (int pos = servo.read(); pos >= targetPosition; pos -= step) {
          servo.write(pos);
          delay(delayTime);
        }
      }

      // Drop the object (you can add your specific actions here)
      drop();
      s.write(posI);
      delay(100);

      // Return to the initial position (90 degrees)
      if (servo.read() != initialPosition) {
        if (servo.read() < initialPosition) {
          for (int pos = servo.read(); pos <= initialPosition; pos += step) {
            servo.write(pos);
            delay(delayTime);
          }
        } else {
          for (int pos = servo.read(); pos >= initialPosition; pos -= step) {
            servo.write(pos);
            delay(delayTime);
          }
        }
      }
    } else {
      //Serial.println("Invalid input. Please enter 1, 2, 3, or 4.");
    }
  }
}

void drop() {
  // put your main code here, to run repeatedly:
  s.write(posI);
  delay(1500);

  s.write(posF);
  delay(1500);

}