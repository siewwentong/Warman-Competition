#include <Servo.h>
const int uSFront = 8;
const int uSFront_1 = 12;
const int uSBack = 11;
const int limitSwitch = 13;

int motorL = 5;
int motorR = 6;
int dirL = 4;
int dirR = 7;

int servoPin1 = 9;
int servoPin2 = 10;
Servo Servo1;
Servo Servo2;

int startagain;

void setup() {
  pinMode (limitSwitch, INPUT_PULLUP);
  pinMode (motorL, OUTPUT);
  pinMode (motorR, OUTPUT);
  pinMode (dirL, OUTPUT);
  pinMode (dirR, OUTPUT);

  Servo1.attach(servoPin1); //servo for translational motion
  Servo2.attach(servoPin2); //servo for rotational motion
  
  Serial.begin(9600);
//  pinMode (startButton, INPUT);

Servo1.write(90);
Servo2.write(90);
}

void loop() {
  
long cm_back, cm_front, cm_front_1, cm_front_2;
int start = 0;

unsigned long startTime, endTime;

delay(2000);

//Servo1.write(80); //arm moving up at low speed
//delay(1100);
//Servo1.write(90);

 cm_front_1 = edgeDetect(uSFront_1);
  while (cm_front_1 > 15){
    Serial.println("startrun");
    startRun();
    delay(20);
    Stop();
    cm_front_1 = edgeDetect(uSFront_1);
  }

  Stop();
  
Serial.println("turn");
 turnLeft();

 Serial.println("front");
  cm_front = edgeDetect(uSFront);
  while (cm_front < 5){
    Serial.println("run");
    moveFWD2();
    //delay(12);
    //Stop();
    cm_front = edgeDetect(uSFront);
  }
   moveBACK();
   delay(20);

  Stop();      
  // arm rotates for 1/4 round to raise the balls
  Servo2.write(80);
  delay(45);
  Servo2.write(90);
  delay(10);

  Servo1.write(100); // arm move down at a moderate speed
  delay(595);
  Servo1.write(90); //arm stop moving down
  delay(10); 
       
startTime = millis();
endTime = millis();
Serial.println("back");
  cm_back = edgeDetect(uSBack);
  Serial.print("elapsed time = ");
  Serial.println(endTime-startTime);
  while ((cm_back < 5) && (endTime-startTime < 10000)){
    Serial.println("reverse");
    moveBACK();
    //delay(15);
    //adjust();
    //delay(20);
    
    //Stop();
    cm_back = edgeDetect(uSBack);
    endTime = millis();

    Serial.print("elapsed time = ");
    Serial.println(endTime-startTime);
  }
  Stop();
  reverseLeft();
  delay(400);
      Servo1.write(80); // move arm upwards at moderate speed
      delay(50);
      Servo1.write(90);

//      //move a little for space to rotate arm
//      moveFWD();
//      delay(300);
//       Stop();

      Servo2.write(85); // turn to scoop up balls
      delay(600);
      Servo2.write(90); //stop turning

      for(int count = 0; count <=3; count++)
      {
        moveFWD();
        delay(50);
        Stop();
        
        Servo2.write(85); // turn to scoop up balls
        delay(50);
        Servo2.write(90); //stop turning
      }

      reverseLeft();
      delay(400);

      //move a little for space to rotate arm
      moveFWD();
      delay(2000);
      Stop();

      Servo1.write(80); // move arm upwards at moderate speed
      delay(1000);
      Servo1.write(90);

       // arm rotates for 5/4 round to raise the balls
      Servo2.write(80);
      delay(950);
      Servo2.write(89.9); 
      delay(10);    

      /*Servo1.write(80); // move arm upwards at moderate speed
      delay(900);
      Servo1.write(90);*/


      //Servo1.write(88); // continue moving up at very low speed (once reach higher than ocean compound)

    
   Serial.println("turn");
   turnLeft_2();
   delay(1800);
   Stop();

   cm_back = edgeDetect(uSBack);
   startTime = millis();
    endTime = millis();
   while((digitalRead(limitSwitch) == HIGH)&&(cm_back < 5))
   {
      moveBACK_slow();
      Serial.println('reverse');
      cm_back = edgeDetect(uSBack);
      endTime = millis();
        Servo2.write(90);
        delay(20);
        Servo2.write(89.9);
        delay(10);
      if (endTime-startTime > 500)
      {
        reverseLeft();
        delay(40);
        Stop();
        startTime = millis();
      }
   }
  Stop();
  delay(50);
  
  cm_front_2 = edgeDetect(uSFront_1);
  while (cm_front_2 > 20){
    Serial.println("startrun");
    startRun();
    Servo2.write(90);
    delay(50);
    Servo2.write(89.9);
    delay(30);
    cm_front_2 = edgeDetect(uSFront_1);
  }

  Stop();
  Servo2.write(90);
  
  Servo1.write(80);
  delay(300);
  Servo1.write(90);

   turnLeft_2();
   delay(1500);
   Stop();

   Serial.println("back");
  cm_back = edgeDetect(uSBack);
  while (cm_back < 5){
    Serial.println("reverse");
    moveBACK();
    cm_back = edgeDetect(uSBack);
  }
  
  Stop();
  moveFWD();
  delay(100);
  Stop();

   Servo2.write(85);
   delay(800);
   Servo2.write(90);
  

  delay(1000000000000000000);
  
}

//functions............................................................
void startRun() {
  digitalWrite(dirL, HIGH);
  digitalWrite(dirR, HIGH);
  analogWrite(motorL, 230);
  analogWrite(motorR, 255);
}
void turnLeft() {
  digitalWrite(dirL, LOW);
  digitalWrite(dirR, HIGH);
  analogWrite(motorL, 240);
  analogWrite(motorR, 255);
  delay(800);
}

void turnLeft_2() {
  digitalWrite(dirL, LOW);
  digitalWrite(dirR, HIGH);
  analogWrite(motorL, 240);
  analogWrite(motorR, 255);
}

void reverseLeft() {
  digitalWrite(dirL, HIGH);
  digitalWrite(dirR, LOW);
  analogWrite(motorL, 240);
  analogWrite(motorR, 255);
}

long edgeDetect(int uS) {
  long duration, cm;
  pinMode(uS, OUTPUT);
  digitalWrite(uS, LOW);
  delayMicroseconds(2);
  digitalWrite(uS, HIGH);
  delayMicroseconds(5);
  digitalWrite(uS, LOW);
  pinMode(uS, INPUT);
  duration = pulseIn(uS, HIGH);
  cm = duration / 29 / 2;
  Serial.print("ultrasonic sensor = ");
  Serial.println(cm);
  return cm;
}
void moveBACK() {
  digitalWrite(dirL, LOW);
  digitalWrite(dirR, LOW);
  analogWrite(motorL, 230);
  analogWrite(motorR, 255);
}

void moveBACK_slow()
{
  digitalWrite(dirL, LOW);
  digitalWrite(dirR, LOW);
  analogWrite(motorL, 150);
  analogWrite(motorR, 150);
}

void moveFWD() {
  digitalWrite(dirL, HIGH);
  digitalWrite(dirR, HIGH);
  analogWrite(motorL, 220);
  analogWrite(motorR, 150);
}

void moveFWD2() {
  digitalWrite(dirL, HIGH);
  digitalWrite(dirR, HIGH);
  analogWrite(motorL, 200);
  analogWrite(motorR, 200);
}

void Stop()
{
   digitalWrite(dirL, HIGH);
  digitalWrite(dirR, HIGH);
  analogWrite(motorL, 0);
  analogWrite(motorR, 0);
}

void adjust() {
  digitalWrite(dirL, HIGH);
  digitalWrite(dirR, LOW);
  analogWrite(motorL, 255);
  analogWrite(motorR, 255);
}

//second forward with slower speed and maybe turn right a little
//make use of back sensor to move forward (when sensor senses less than 5 cm, stop moving forward)
//move forward more (and turn right) before scopping up to raise the balls
