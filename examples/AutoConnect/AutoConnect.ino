#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


void setup() {
	// put your setup code here, to run once:
	Serial1.begin(9600);
	Serial1.println("Printed From Uart1");
	//WiFiManager
	//Local intialization. Once its business is done, there is no need to keep it around
	//WiFiManager wifiManager;
	//reset saved settings
	//wifiManager.resetSettings();

	//set custom ip for portal
	//wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

	//fetches ssid and pass from eeprom and tries to connect
	//if it does not connect it starts an access point with the specified name
	//here  "AutoConnectAP"
	//and goes into a blocking loop awaiting configuration
	//wifiManager.autoConnect("AutoConnectAP");
	//or use this for auto generated name ESP + ChipID
	//WiFiMnager.autoConnect();


	//if you get here you have connected to the WiFi
	//Serial1.println("connected...yeey :)");
}

void loop() {
	// put your main code here, to run repeatedly:
	Serial1.println("OK");
	delay(400);

}
