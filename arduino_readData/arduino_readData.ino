#include <Servo.h>
#include <string.h>

#define led 7
#define servo_motor 13

Servo motor;
int pos = 0;

char received_data;
bool newData = false;

void receiveData(){
  if(Serial.available() > 0){
    received_data = Serial.read();
    newData = true;
  }
}

bool IsFound(){
  if(newData){
    if(received_data == 'Y'){
      return true;
    }
  }

  return false;
} 

void rotate(){
  for(pos = 0; pos <= 180; pos++){
    motor.write(pos);
    if(IsFound())
      break;
    delay(15);
  }

  for(pos = 180; pos >= 0; pos--){
    motor.write(pos);
    if(IsFound())
      break;
    delay(15);
  }
}

void setup(){
  Serial.begin(115200);

  motor.attach(servo_motor);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}

void loop(){
  receiveData();

  bool t = IsFound();

  if(t){
    rotate();
    digitalWrite(led, LOW);
  }

  newData = false;
}