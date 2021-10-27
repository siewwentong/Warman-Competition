#include <Servo.h>
int servoPin1 = 9;
int servoPin2 = 10;
int power = 13;
Servo Servo1;
Servo Servo2;

void setup() {
  // put your setup code here, to run once:
  pinMode(power,OUTPUT);
  Servo1.attach(servoPin1);
  Servo2.attach(servoPin2);
  Serial.begin(9600);
}

void loop() {

  
  //to contain all balls (rolling 1.25 round)
  Servo2.write(85);
  Serial.println(85);
  delay(1800);
  Servo2.write(90);
  Serial.println(90);
  delay(10000000000000000);
  

  
  //to release the balls
    Servo2.write(95);
  Serial.println(95);
  delay(1800);
  Servo2.write(90);
  Serial.println(90);
  delay(10000000000000000);

  /*
  //to move arm up to ocean compound
  Servo2.write(90);
  Servo1.write(80);
  delay(1000);
  Servo1.write(90);
  delay(1000000000000000000);
  */

Servo1.write(80); //go up
delay(800);
Servo1.write(90);
delay(2000);
//collecting ball code here
Servo1.write(100);  //go down
delay(800);
Servo2.write(90);
Servo1.write(90);
delay(2000);
Servo1.write(80);
delay(1600);
Servo1.write(90);
delay(2000);
Servo1.write(100);
delay(1600);
Servo1.write(90);
delay(10000000000);
  
   
}

/*notes:
 Servo 1: <90 go up
 speed 80, 1s go up 11cm
 
 Servo 2: <90 scoop up,
 89 scoop up at low speed (92 in reverse)
 
 */

//void moveUp()
//{
//  initial_pos = Servo1.read();
//  int j = 10;
//  for (int i = initial_pos; i<pos_up; i+=2)
//  {
//    Servo1.write(i);
//    Serial.print("servo position = ");
//    Serial.println(i);
//    if (j<72) //clockwise
//  {
//  Serial.print("servo direction = ");
//  Serial.println(j);
//  Servo2.write(j);
//  }
//  else
//  {
//  Serial.print("servo direction = ");
//  Serial.println("71");
//    Servo2.write(71);
//  }
//  j+=2;
//    delay(200);
//  }
//}
//
//void moveDown()
//{
//  initial_pos = Servo1.read();
//  int j = 140;
//  for (int i = initial_pos; i>pos_down; i--)
//  {
//    Servo1.write(i);
//    Serial.print("servo position = ");
//    Serial.println(i);
//    if (j>71) //clockwise
//  {
//  Serial.print("servo direction = ");
//  Serial.println(j);
//  Servo2.write(j);
//  j-=2;
//  }
//  else
//  {
//  j = 71;
//  Serial.print("servo direction = ");
//  Serial.println("71");
//    Servo2.write(71);
//  }
//    delay(200);
//  }
//}
