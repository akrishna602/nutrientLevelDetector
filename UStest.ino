#include <HCSR04.h>
UltraSonicDistanceSensor US(12, 13); // Initialize sensor that uses digital pins trig and echo.
float x=100;
int LED1 = 10;
int LED2 = 9;
int LED3 = 8;
int LED4 = 7;
int LED5 = 6;
int LED6 = 5;  //Buzzer pin
int MOTOR=10;


void setup()
{
  Serial.begin(9600);
   pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  
  delay(500);
}

void loop()
{
float distance = US.measureDistanceCm();

  
  if (distance > 0.86*x)
  {

    digitalWrite(MOTOR, HIGH);
    digitalWrite(5, HIGH);
    Serial.println("Empty tank");
    delay(100);
  }



  
  else if (distance > .76*x && distance < .85*x)
  {
    digitalWrite(6, HIGH);
    Serial.println("nearly empty"); 
  }




 else if (distance < .75*x && distance > .5*x)
  {
    Serial.println("nearly empty");
    digitalWrite(7, HIGH); 
  }


 else if (distance < .5*x && distance > .26*x)
  {
    Serial.println("nearly empty");
    digitalWrite(8, HIGH);  
  }


   else if (distance < .25*x && distance > .1*x)
  {
    Serial.println("nearly empty");
    digitalWrite(9, HIGH);
  }
  

  else if (distance <= .1*x) // check if water is full
  {
    digitalWrite(10, HIGH);
    Serial.println("full tank");
    delay(1000);

    
  }
  delay(1000);
}
