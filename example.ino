#include <DHT11Interface.h>

// Sensor pin numbers are counted left to right
// with sensor side (not label side) facing you
// and pins pointed down.

// Connect pin 1 on sensor to VCC (3-5.5 V)
// Connect pin 2 on sensor to input 2 on Arduino
// Pin 3 on sensor doesn't do anything, so ignore it
// Connect pin 4 on sensor to ground.

// More about the sensor at http://www.micro4you.com/files/sensor/DHT11.pdf

#define DHTPIN 2

DHT11Interface *dht11int;
int readingCount;

void setup()
{
  dht11int = new DHT11Interface(DHTPIN);
  readingCount = 0;
  Serial.begin(115200);
  Serial.println("DHT11 TEST PROGRAM ");
  Serial.println();
}

void loop()
{
  delay(1500);  // DHT11 library recommends not taking the first reading for at least 1 second.
  readingCount++;
  Serial.println(readingCount);
  Serial.println(dht11int->status());
  Serial.println(dht11int->celsius());
  Serial.println(dht11int->humidity());
}
