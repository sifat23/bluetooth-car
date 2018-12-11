#include <AFMotor.h>

AF_DCMotor rbmotor(1, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor rfmotor(2, MOTOR12_64KHZ);
AF_DCMotor lfmotor(3, MOTOR12_64KHZ);
AF_DCMotor lbmotor(4, MOTOR12_64KHZ);

int speedmax = 100;

int tx=1;
int rx=0;
char inSerial[15];


void setup(){
  Serial.begin(9600);

  rbmotor.setSpeed(speedmax);
  rfmotor.setSpeed(speedmax);
  lbmotor.setSpeed(speedmax);
  lfmotor.setSpeed(speedmax);// set the speed to 200/255
  
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
}

void loop(){
  int i=0;
  int m=0;
  delay(500);
  if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      inSerial[i]=Serial.read();
      i++;
    }
    inSerial[i]='\0';
    Check_Protocol(inSerial);
  }
}

void Check_Protocol(char inStr[]){
  int i=0;
  int m=0;
  Serial.println(inStr);
  
  //going forward
  if(!strcmp(inStr,"2forward")){
    moveForward();
    Serial.println("going forward");
    for(m=0;m<11;m++){
      inStr[m]=0;
    }
    i=0;
  }
  
  //going back
  if(!strcmp(inStr,"2back")){
    moveBackward();
    Serial.println("going back");
    for(m=0;m<11;m++){
      inStr[m]=0;
    }
    i=0;
  }
  
  //turn right
  if(!strcmp(inStr,"2right")){
    turnRight();
    Serial.println("going right");
    for(m=0;m<11;m++){
      inStr[m]=0;
    }
    i=0;
  }

  //turn left
  if(!strcmp(inStr,"2left")){
    turnLeft();
    Serial.println("going left");
    for(m=0;m<11;m++){
      inStr[m]=0;
    }
    i=0;
  }
  
  //making stop
  if(!strcmp(inStr,"2stop")){
      moveStop();
      Serial.println("stop");
      for(m=0;m<11;m++){
        inStr[m]=0;
      }
      i=0;
  } else {
    for(m=0;m<11;m++){
  inStr[m]=0;
  }
  i=0;
  }
}

void moveStop()
{
  rbmotor.run(RELEASE);
  rfmotor.run(RELEASE);
  lbmotor.run(RELEASE);
  lfmotor.run(RELEASE);
}

void moveForward()
{
    lfmotor.run(FORWARD);
    lbmotor.run(FORWARD);
    rfmotor.run(FORWARD);
    rbmotor.run(FORWARD);
}

void moveBackward()
{
  lbmotor.run(BACKWARD);
  lfmotor.run(BACKWARD);
  rbmotor.run(BACKWARD);
  rfmotor.run(BACKWARD);
}

void turnRight()
{
  lfmotor.run(FORWARD);
  lbmotor.run(FORWARD);
  rfmotor.run(BACKWARD);
  rbmotor.run(BACKWARD);
}

void turnLeft()
{
  rbmotor.run(FORWARD);
  rfmotor.run(FORWARD);
  lbmotor.run(BACKWARD);
  lfmotor.run(BACKWARD);
}
