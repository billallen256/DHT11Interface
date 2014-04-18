#include <DHT11Interface.h>
#include <SD.h>

// Sensor pin numbers are counted left to right
// with sensor side (not label side) facing you
// and pins pointed down.

// Connect pin 1 on sensor to VCC (3-5.5 V)
// Connect pin 2 on sensor to input 2 on Arduino
// Pin 3 on sensor doesn't do anything, so ignore it
// Connect pin 4 on sensor to ground.

// More about the sensor at http://www.micro4you.com/files/sensor/DHT11.pdf

const int DHTPIN = 2;
const int CHIP_SELECT = 4;
const int INTERVAL = 15; // seconds

DHT11Interface *dht11int;
float tempReadings[INTERVAL];
float humidityReadings[INTERVAL];
float dewReadings[INTERVAL];
int readingIndex;
bool firstIter;

void setup()
{
  dht11int = new DHT11Interface(DHTPIN);
  readingIndex = 0;
  firstIter = false;
  
  for (int i = 0 ; i < INTERVAL ; ++i) {
    tempReadings[i] = 0.0;
    humidityReadings[i] = 0.0;
    dewReadings[i] = 0.0;
  }
  
  Serial.begin(9600);
  Serial.println("DHT11 Logger");
  Serial.print("Initializing SD card...");
  
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("initialization failed!");
    return;
  }
  
  Serial.println("initialization done.");
  
  if (SD.exists("log.csv")) {
    Serial.println("log.csv exists... removing");
    SD.remove("log.csv");
  } else {
    Serial.println("log.csv doesn't exist.");  
  }
}

float average(float readings[], int length) {
  float sum = 0.0;
  
  for (int i = 0 ; i < length ; ++i) {
    sum += readings[i];
  }
  
  return sum / (float) length;
}

void loop()
{
  delay(1000);  // DHT11 library recommends not taking the first reading for at least 1 second.
  Serial.println(readingIndex);

//  for (int i = 0 ; i < INTERVAL ; ++i) {
//    Serial.print("[");
//    Serial.print(tempReadings[i]);
//    Serial.print(",");
//    Serial.print(humidityReadings[i]);
//    Serial.print(","); 
//    Serial.print(dewReadings[i]);
//    Serial.print("]");
//  }
//  
//  Serial.println();
  
  if (readingIndex == 0 && firstIter == true) {
    Serial.println(readingIndex, 3);
    String status = dht11int->status();
    float temp = average(tempReadings, INTERVAL);
    Serial.println(temp, 3);
    float humidity = average(humidityReadings, INTERVAL);
    Serial.println(humidity, 3);
    float dew = average(dewReadings, INTERVAL);
    Serial.println(dew, 3);

    File dataFile = SD.open("log.csv", FILE_WRITE);
    
    if (dataFile) {
      dataFile.print(temp, 3);
      dataFile.print(",");
      dataFile.print(humidity, 3);
      dataFile.print(",");
      dataFile.print(dew, 3);
      dataFile.println();
      Serial.println(" ...WRITTEN");
      dataFile.close();
    } else {
      Serial.println(" ...FAILED");
    }
  } else {
    if (dht11int->status() == "AOK") {
      tempReadings[readingIndex] = dht11int->celsius();
      humidityReadings[readingIndex] = dht11int->humidity();
      dewReadings[readingIndex] = dht11int->dewPoint();
    }
  }

  if (readingIndex + 1 == INTERVAL) {
    firstIter = true;
  }

  readingIndex = (readingIndex + 1) % INTERVAL;
}

