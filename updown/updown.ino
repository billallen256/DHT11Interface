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
#define HISTORY_SIZE 10

DHT11Interface *dht11int;
float readings[HISTORY_SIZE];
int readingIndex;

void setup()
{
  dht11int = new DHT11Interface(DHTPIN);
  readingIndex = 0;
  
  for (int i = 0 ; i < HISTORY_SIZE ; ++i) {
    readings[i] = 0.0;
  }
  
  Serial.begin(115200);
  Serial.println("DHT11 TEST PROGRAM ");
  Serial.println();
}

float average(float readings[]) {
  float sum = 0.0;
  
  for (int i = 0 ; i < HISTORY_SIZE ; ++i) {
    sum += readings[i];
  }
  
  return sum / (float) HISTORY_SIZE;
}

void loop()
{
  delay(1500);  // DHT11 library recommends not taking the first reading for at least 1 second.
  String status = dht11int->status();
  Serial.print(status);
  Serial.print(" ");
  
  if (status == "AOK") {
    float reading = dht11int->celsius();
    Serial.print(reading, 3);
    Serial.print(" ");
    readings[readingIndex] = reading;
    readingIndex = (readingIndex + 1) % HISTORY_SIZE;
    
    Serial.print("[");
    for (int i = 0 ; i < HISTORY_SIZE ; ++i) {
      Serial.print(readings[i], 3);
      Serial.print(",");
    }
    Serial.print("]");
    
    float avg = average(readings);
    Serial.print("=");
    Serial.print(avg, 3);
    
    if (reading > avg) {
      Serial.print(" Incr");
    } else if (reading == avg) {
      Serial.print(" Hold");
    } else {
      Serial.print(" Decr");
    }
  }
  
  Serial.println();
}
