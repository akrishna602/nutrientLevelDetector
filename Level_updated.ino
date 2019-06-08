#include <HCSR04.h>
#include <dht11.h>
#define DHT11PIN 4
dht11 DHT11;
#define FAN 3
#define HEATER 2
#define HUMIDIFIER 11


UltraSonicDistanceSensor US(12, 13); // Initialize trig and echo.
float x = 24; //x determines the tank length
int LED1 = 10; //Nutrient tank is full
int LED2 = 9; //75% filled
int LED3 = 8; //50% filled
int LED4 = 7; //50% filled
int LED5 = 6; //25% filled
int LED6 = 5; //Buzzer beeps when tank is empty

void setup()
{
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(FAN, OUTPUT);
  pinMode(HEATER, OUTPUT);
  pinMode(HUMIDIFIER, OUTPUT);

  delay(500);
}

void loop()
{
  Serial.println();
  dh();
  us();


}


void dh() {
  Serial.println();
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  float humidity = DHT11.humidity;
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (C): ");
  float temp = DHT11.temperature;
  Serial.println((float)DHT11.temperature, 2);

  if (temp < 24) {
    Serial.println("LOW temperature");
    digitalWrite(HEATER, LOW);
    digitalWrite(FAN, HIGH);
  }
  else if (temp > 30) {
    Serial.println("High temperature");
    digitalWrite(FAN, LOW);
    digitalWrite(HEATER, HIGH);
  }

  else if (temp > 24 || temp < 30) {
    Serial.println("Favourable Temperature");
    digitalWrite(FAN, HIGH);
    digitalWrite(HEATER, HIGH);
  }

  if (humidity < 70) {
    Serial.println("Low moisture");
    digitalWrite(HUMIDIFIER, LOW);
  }
  else if (humidity > 75) {
    Serial.println("Favourable moisture");
    digitalWrite(HUMIDIFIER, HIGH);
  }



  delay(100);
}



void us() {
  float distance = US.measureDistanceCm();
  if (distance > 0.86 * x)
  {
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    Serial.println("Empty tank");
    delay(100);
  }

  else if (distance > .76 * x && distance < .85 * x)
  {
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    Serial.println("5th led balyo");
    delay(100);
  }

  else if (distance < .75 * x && distance > .5 * x)
  {
    Serial.println("4th led balyo");
    digitalWrite(5, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    delay(100);
  }


  else if (distance < .5 * x && distance > .26 * x)
  {
    Serial.println("3rd led balyo");
    digitalWrite(5, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(10, LOW);
    delay(100);
  }


  else if (distance < .25 * x && distance > .1 * x)
  {
    Serial.println("alikai ghatyo");
    digitalWrite(5, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    delay(100);
  }

  else if (distance <= .1 * x) // check if water is full
  {
    digitalWrite(5, LOW);
    digitalWrite(10, HIGH);
    Serial.println("Full tank");
    delay(100);
  }
  delay(100);
}
