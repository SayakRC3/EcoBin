#include <Servo.h>
int posF=20; //drop position
int posI=80; //dump pos

int iniPos=90; //for the base motor

Servo s;
int sPin=9; //reciever servo
void setup() {
  // put your setup code here, to run once:
  s.attach(sPin);
  s.write(90);
  s.write(iniPos);
  
}

void loop() {
  // put your main code here, to run repeatedly:
}
