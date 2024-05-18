#include <SPI.h>
#include <Ethernet.h>

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>

#define MOTORCH1PIN 4
#define MOTORCH2PIN 5
#define MOTORCH3PIN 6
#define MOTORCH4PIN 7
#define MOTORCH5PIN 8
#define MOTORCH6PIN 9
#define MOTORCH7PIN 2
#define MOTORCH8PIN 3

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFF, 0x02
};
IPAddress ip(192, 168, 3, 101); // The IP address will be dependent on your local network:

EthernetServer ethServer(502);

ModbusTCPServer modbusTCPServer;

void setup() {
  Serial.begin(9600);
  pinMode(MOTORCH1PIN, OUTPUT);
  // put your setup code here, to run once:
  Serial.println("Begin Ethernet Shield!");
  Serial.println("Initialize Ethernet with DHCP:");

  Ethernet.begin(mac, ip);

  // print your local IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());

  // start the server
  ethServer.begin();
  
  // start the Modbus TCP server
  if (!modbusTCPServer.begin()) {
    Serial.println("Failed to start Modbus TCP Server!");
    while (1);
  }

  modbusTCPServer.configureHoldingRegisters(0x00, 8);
}

void loop() {
  // put your main code here, to run repeatedly:
  EthernetClient client = ethServer.available();
  
  if (client) {
    // a new client connected
    Serial.println("new client");

    // let the Modbus TCP accept the connection 
    modbusTCPServer.accept(client);

    while (client.connected()) {
      // poll for Modbus TCP requests, while client connected
      modbusTCPServer.poll();
      motorUpdate();
    }

    Serial.println("client disconnected");
  }
}

void motorUpdate(){
  int motorCh1Val = modbusTCPServer.holdingRegisterRead(0x00);
  if (motorCh1Val > 100) {
    motorCh1Val = 100;
    modbusTCPServer.holdingRegisterWrite(0x00, motorCh1Val);
  } else if (motorCh1Val < 0) {
    motorCh1Val = 0;
    modbusTCPServer.holdingRegisterWrite(0x00, motorCh1Val);
  }
  int motorCh2Val = modbusTCPServer.holdingRegisterRead(0x01);
  if (motorCh2Val > 100) {
    motorCh2Val = 100;
    modbusTCPServer.holdingRegisterWrite(0x01, motorCh2Val);
  } else if (motorCh2Val < 0) {
    motorCh2Val = 0;
    modbusTCPServer.holdingRegisterWrite(0x01, motorCh2Val);
  }
  int motorCh3Val = modbusTCPServer.holdingRegisterRead(0x02);
  if (motorCh3Val > 100) {
    motorCh3Val = 100;
    modbusTCPServer.holdingRegisterWrite(0x02, motorCh3Val);
  } else if (motorCh3Val < 0) {
    motorCh3Val = 0;
    modbusTCPServer.holdingRegisterWrite(0x02, motorCh3Val);
  }
  int motorCh4Val = modbusTCPServer.holdingRegisterRead(0x03);
  if (motorCh4Val > 100) {
    motorCh4Val = 100;
    modbusTCPServer.holdingRegisterWrite(0x03, motorCh4Val);
  } else if (motorCh4Val < 0) {
    motorCh4Val = 0;
    modbusTCPServer.holdingRegisterWrite(0x03, motorCh4Val);
  }
  int motorCh5Val = modbusTCPServer.holdingRegisterRead(0x04);
  if (motorCh5Val > 100) {
    motorCh5Val = 100;
    modbusTCPServer.holdingRegisterWrite(0x04, motorCh5Val);
  } else if (motorCh5Val < 0) {
    motorCh5Val = 0;
    modbusTCPServer.holdingRegisterWrite(0x04, motorCh5Val);
  }
  int motorCh6Val = modbusTCPServer.holdingRegisterRead(0x05);
  if (motorCh6Val > 100) {
    motorCh6Val = 100;
    modbusTCPServer.holdingRegisterWrite(0x05, motorCh6Val);
  } else if (motorCh6Val < 0) {
    motorCh6Val = 0;
    modbusTCPServer.holdingRegisterWrite(0x05, motorCh6Val);
  }
  int motorCh7Val = modbusTCPServer.holdingRegisterRead(0x06);
  if (motorCh7Val > 100) {
    motorCh7Val = 100;
    modbusTCPServer.holdingRegisterWrite(0x06, motorCh7Val);
  } else if (motorCh7Val < 0) {
    motorCh7Val = 0;
    modbusTCPServer.holdingRegisterWrite(0x06, motorCh7Val);
  }
  int motorCh8Val = modbusTCPServer.holdingRegisterRead(0x07);
  if (motorCh8Val > 100) {
    motorCh8Val = 100;
    modbusTCPServer.holdingRegisterWrite(0x07, motorCh8Val);
  } else if (motorCh8Val < 0) {
    motorCh8Val = 0;
    modbusTCPServer.holdingRegisterWrite(0x07, motorCh7Val);
  }

  int motorCh1Pwm = motorCh1Val * 255 / 100;
  int motorCh2Pwm = motorCh2Val * 255 / 100;
  int motorCh3Pwm = motorCh3Val * 255 / 100;
  int motorCh4Pwm = motorCh4Val * 255 / 100;
  int motorCh5Pwm = motorCh5Val * 255 / 100;
  int motorCh6Pwm = motorCh6Val * 255 / 100;
  int motorCh7Pwm = motorCh7Val * 255 / 100;
  int motorCh8Pwm = motorCh8Val * 255 / 100;

  analogWrite(MOTORCH1PIN, motorCh1Pwm);
  analogWrite(MOTORCH2PIN, motorCh2Pwm);
  analogWrite(MOTORCH3PIN, motorCh3Pwm);
  analogWrite(MOTORCH4PIN, motorCh4Pwm);
  analogWrite(MOTORCH5PIN, motorCh5Pwm);
  analogWrite(MOTORCH6PIN, motorCh6Pwm);
  analogWrite(MOTORCH7PIN, motorCh7Pwm);
  analogWrite(MOTORCH8PIN, motorCh8Pwm);
}
