//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseRoom_ESP8266 is a sample that demo using multiple sensors
// and actuactor with the FirebaseArduino library.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "iotdev-6b58b.firebaseio.com"
#define FIREBASE_AUTH "5zg8yd7bazlRj0heqBZvrduyyjykvshtRPCbjlYh"
#define WIFI_SSID "AutonomousDevice"
#define WIFI_PASSWORD "autonomous123"
byte mac[6];
void wifiSetup(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial1.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial1.print(".");
    delay(500);
  }
  Serial1.println();
  Serial1.print("connected: ");
  Serial1.println(WiFi.localIP()); 
  Serial1.print("MAC: "); 
  WiFi.macAddress(mac);
  Serial1.print("MAC: ");
  Serial1.print(mac[5],HEX);
  Serial1.print(":");
  Serial1.print(mac[4],HEX);
  Serial1.print(":");
  Serial1.print(mac[3],HEX);
  Serial1.print(":");
  Serial1.print(mac[2],HEX);
  Serial1.print(":");
  Serial1.print(mac[1],HEX);
  Serial1.print(":");
  Serial1.println(mac[0],HEX);
}
void firebaseSetup(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    if (Firebase.failed() == true) {
    Serial1.print("Setup Error: ");
    Serial1.println(Firebase.error());
  }   
  else
  {
    Serial1.println("Setup OK: ");
  }
	Firebase.stream("/devices/4425788");
	if (Firebase.failed())
	{
		Serial1.println("Setup stream fail");
	}
	else
	{
		Serial1.println("Setup Stream success");
	}

}
void setup() {
  Serial1.begin(9600);
  wifiSetup();
  firebaseSetup();
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  Serial1.print("Chip ID ");
  Serial1.println(ESP.getChipId());
}
void firebaseStream()
{
	if (Firebase.available())
	{
		FirebaseObject event = Firebase.readEvent();
		String eventType = event.getString("type");
		eventType.toLowerCase();
		Serial1.print("event:");
		Serial1.println(eventType);

	}

}
void loop() {
	if (Firebase.available())
	{
		FirebaseObject event = Firebase.readEvent();
		String eventType = event.getString("type");
		//eventType.toLowerCase();
		Serial1.print("event:");
		Serial1.println(eventType);
		Serial1.print("data: ");
		Serial1.println(event.getString("data"));
		

	}
	
	delay(100);
}
