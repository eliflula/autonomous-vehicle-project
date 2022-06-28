#include "NewPing.h"
#include <Servo.h> 

Servo myservo; 

#define max_uzaklik 100 

int distance = 100;

int trigPin1 = 6;
int echoPin1 = 7;

int MotorLE = 8;  //sol motor hız pini
int MotorL1 = 10;  //sol motor ileri pini
int MotorL2 = 9; //sol motor geri pini

int MotorRE = 13; //sağ motor hız pini
int MotorR1 = 12; //sağ motor ileri pini
int MotorR2 = 11; //sağ motor geri pini

int state;


NewPing sonar(trigPin1, echoPin1, max_uzaklik);

void setup() 
{
  myservo.attach(5);
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  
  pinMode(echoPin1,INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorLE, OUTPUT);
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorRE, OUTPUT);
  
  Serial.begin(9600);
}

void loop() 
{
  int distanceR = 0;
  int distanceL =  0;
  delay(40);

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);  
  digitalWrite(trigPin1, HIGH);   
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW); 
  
  Serial.print("Sensör bilgi: "); 
  Serial.print(distance); 
  Serial.println(" CM "); 
  delay(100);
  
 
      if(distance<=50)
     {
        dur();
        delay(200);
        geri();
        delay(500);
        dur();
        delay(200);
        distanceR = sagabak();
        delay(300);
        distanceL = solabak();
        delay(300);
    
        if(distanceR>=distanceL)
        {
          sag();
          delay(500);
          ileri();
        }
        else
        {
          sol();
          delay(500);
          ileri();
        }
       }
       else
       {
        ileri();
       }
  
 distance = readPing();
 
}

void ileri()
{  

  digitalWrite(MotorR1, HIGH); 
  digitalWrite(MotorR2, LOW); 
  analogWrite(MotorRE, 130);

  digitalWrite(MotorL1, HIGH); 
  digitalWrite(MotorL2, LOW); 
  analogWrite(MotorLE, 130); 

}

void dur()
{  

  digitalWrite(MotorR1, LOW); 
  digitalWrite(MotorR2, LOW); 
  analogWrite(MotorRE, 0);

  digitalWrite(MotorL1, LOW); 
  digitalWrite(MotorL2, LOW); 
  analogWrite(MotorLE, 0); 

}

void sag()
{ 

  digitalWrite(MotorR1, HIGH); 
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 0);

  digitalWrite(MotorL1, HIGH); 
  digitalWrite(MotorL2, LOW); 
  analogWrite(MotorLE, 150); 
  
  
}

void sol()
{ 

  digitalWrite(MotorR1, HIGH); 
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 150);

  digitalWrite(MotorL1, HIGH); 
  digitalWrite(MotorL2, LOW); 
  analogWrite(MotorLE, 0); 
   
}

void geri()
{ 

  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  analogWrite(MotorRE, 150); 

  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH); 
  analogWrite(MotorLE, 150); 
  
}

int sagabak()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int solabak()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

int readPing() 
{ 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}
