#include <Ethernet.h>       // Ethernet library v2 is required
#include <ModbusEthernet.h>

#include <Wire.h>
#include <MS5x.h>
#include <Math.h>

#include "DHT.h"

#define DHTPIN 4     // Digital pin connected to the DHT sensor
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// DHT Object
DHT dht(DHTPIN, DHTTYPE);

struct DHTData {
  double temperature;
  double humidity;
};

// MS5611 Data

struct MS5611Data {
  double pressure;
  double temperature;
};

// MS5611 object
MS5x barometer(&Wire);

// Modbus Registers Offsets
const int TEMP_HREG = 100;
const int HUMID_HREG = 101;
const int TEMP_MS5611_HREG = 102;
const int PRESS_MS5611_HREG = 103;

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03
};
IPAddress ip(192, 168, 3, 203); // The IP address will be dependent on your local network:
ModbusEthernet mb;              // Declare ModbusTCP instance

void setup() {
  Serial.println("Begin Ethernet Shield!");
  Serial.println("Initialize Ethernet with DHCP:");

  Serial.begin(115200);
  Ethernet.init(5);        // SS pin
  Ethernet.begin(mac, ip);

  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());

  // start the server
  mb.server();
  mb.addHreg(TEMP_HREG);
  mb.addHreg(HUMID_HREG);
  mb.addHreg(PRESS_MS5611_HREG);
  mb.addHreg(TEMP_MS5611_HREG);

	Serial.println(F("DHTxx test!"));
  dht.begin();

  while(barometer.connect()>0) { // barometer.connect starts wire and attempts to connect to sensor
		Serial.println(F("Error connecting..."));
		delay(500);
	}
}

void loop() {
	mb.task();

  DHTData sensorData = getSensorData();
  mb.Hreg(TEMP_HREG, round(sensorData.temperature*10));
  mb.Hreg(HUMID_HREG, round(sensorData.humidity*10));

  MS5611Data sensorMS5611Data = getMS5611SensorData();
  mb.Hreg(PRESS_MS5611_HREG, round(sensorMS5611Data.pressure));
  mb.Hreg(TEMP_MS5611_HREG, round(sensorMS5611Data.temperature*10));

  delay(250);
}

DHTData getSensorData() {
  DHTData newData;
  double humidity=0;
	double temperature=0;

	double h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  double t = dht.readTemperature();

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.println("");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("");

  newData.temperature = t;
  newData.humidity = h;

  return newData;
}

MS5611Data getMS5611SensorData() {
  MS5611Data newData;
  double pressure=0;
	double temperature=0;
	barometer.checkUpdates();

	if (barometer.isReady()) { 
		temperature = barometer.GetTemp(); // Returns temperature in C 
		pressure = barometer.GetPres()/100; // Returns pressure in mbar
    
    delay(100);
	}
  newData.temperature = temperature;
  newData.pressure = pressure;

  return newData;
}
