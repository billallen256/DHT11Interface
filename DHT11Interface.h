#ifndef DHT11Interface_h
#define DHT11Interface_h

#include <Arduino.h>
#include <stdlib.h>

#include "dht11.h"

class DHT11Interface {
public:
	DHT11Interface(int);
	float humidity();
	float celsius();
	float fahrenheit();
	float kelvin();
	float dewPoint();

	String humidityStr();
	String celsiusStr();
	String fahrenheitStr();
	String kelvinStr();
	String dewPointStr();

	String ftos(float);
	String status();

private:
	dht11 DHT11;
	int dht11pin;
};

#endif
