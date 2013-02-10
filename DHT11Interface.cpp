#include "DHT11Interface.h"

DHT11Interface::DHT11Interface(int pin) {
	dht11pin = pin;
}

String DHT11Interface::status() {
	int chk = DHT11.read(dht11pin);
	String status = "UNK";

	switch (chk)
	{
		case DHTLIB_OK: 
			status = "AOK";
			break;
		case DHTLIB_ERROR_CHECKSUM: 
			status = "ECS";
			break;
		case DHTLIB_ERROR_TIMEOUT: 
			status = "ETO";
			break;
		default: 
			status = "UNK";
			break;
	}

	return status;
}

float DHT11Interface::celsius() {
	return (float)DHT11.temperature;
}

float DHT11Interface::humidity() {
	return (float)DHT11.humidity;
}

float DHT11Interface::fahrenheit() {
	return 1.8 * this->celsius() + 32;
}

float DHT11Interface::kelvin() {
	return this->celsius() + 273.15;
}

// dewPoint function NOAA
// reference: http://wahiduddin.net/calc/density_algorithms.htm 
float DHT11Interface::dewPoint() {
	double celsius = (double) (this->celsius());
	double humidity = (double) (this->humidity());
	double A0 = 373.15/(273.15 + celsius);
	double SUM = -7.90298 * (A0-1);
	SUM += 5.02808 * log10(A0);
	SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
	SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
	SUM += log10(1013.246);
	double VP = pow(10, SUM-3) * humidity;
	double T = log(VP/0.61078);   // temp var
	return (241.88 * T) / (17.558-T);
}

String DHT11Interface::humidityStr() {
	return ftos(humidity());
}

String DHT11Interface::celsiusStr() {
	return ftos(celsius());
}

String DHT11Interface::fahrenheitStr() {
	return ftos(fahrenheit());
}

String DHT11Interface::kelvinStr() {
	return ftos(kelvin());
}

String DHT11Interface::dewPointStr() {
	return ftos(dewPoint());
}

String DHT11Interface::ftos(float value) {
	char temp[10];
	dtostrf((double)value, 7, 2, temp);
	return String(temp);
}
