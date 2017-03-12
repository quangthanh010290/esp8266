#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "iotdev-6b58b.firebaseio.com"
#define FIREBASE_AUTH "5zg8yd7bazlRj0heqBZvrduyyjykvshtRPCbjlYh"
#define WIFI_SSID "AutonomousSale"
#define WIFI_PASSWORD "autonomous123"
bool l1 = false;
bool firstTime = true;
void firebaseSetup() {
	Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
	if (Firebase.failed() == true) {
		Serial.print("Setup Error: ");
		Serial.println(Firebase.error());
	}
	else {
		Serial.println("Setup OK: ");
	}
}
void getFirebaseData() {
	FirebaseObject obj = Firebase.get("123/states");
	if (Firebase.failed() == true) {
		Serial.print("Reading Error: ");
		Serial.println(Firebase.error());
	}
	else {
		bool led1 = obj.getBool("001");
		if (firstTime == true) {
			firstTime = false;
			l1 = led1;
			
			Serial.print("Led1:");
			Serial.println(led1);
			digitalWrite(LED_BUILTIN, !l1);
		}
		else {
			if (l1 != led1) {
				Serial.print("Led1:");
				Serial.println(led1);
				l1 = led1;
				digitalWrite(LED_BUILTIN, !l1);
			}
		}
	}

}
void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);

	//WiFiManager
	//Local intialization. Once its business is done, there is no need to keep it around
	WiFiManager wifiManager;
	//reset saved settings
	//wifiManager.resetSettings();

	//set custom ip for portal
	//wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

	//fetches ssid and pass from eeprom and tries to connect
	//if it does not connect it starts an access point with the specified name
	//here  "AutoConnectAP"
	//and goes into a blocking loop awaiting configuration
	wifiManager.autoConnect("AutoConnectAP");
	//or use this for auto generated name ESP + ChipID
	//wifiManager.autoConnect();


	//if you get here you have connected to the WiFi
	Serial.println("connected...yeey :)");
	pinMode(LED_BUILTIN, OUTPUT);
	firebaseSetup();

}

void loop() {
	// put your main code here, to run repeatedly:
	getFirebaseData();
}