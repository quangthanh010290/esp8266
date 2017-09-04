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
#define WIFI_SSID "Oc Gao 2017"
#define WIFI_PASSWORD "250508th@ah"
String chipId = "123";
byte mac[6];
bool l1 = false;
bool l2 = false;
bool l3 = false;
bool firstTime = true;
bool button_status = false;
void wifiSetup(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP()); 
  Serial.print("MAC: "); 
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);  
}
void firebaseSetup(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
    if (Firebase.failed() == true) {
    Serial.print("Setup Error: ");
    Serial.println(Firebase.error());
  }   
  else{
    Serial.println("Setup OK: ");
    }
}
void setup() {
  Serial.begin(9600);
  wifiSetup();
  firebaseSetup();
  pinMode(D7,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D6,INPUT);
  digitalWrite(D7,LOW);
  digitalWrite(D1,LOW);
  Serial.print("Chip ID ");
  Serial.println(ESP.getChipId());
  button_status = (bool)digitalRead(D6);
  Serial.print("Button: ");
  Serial.println(button_status);
}
void getInput(void)
{
  bool x = (bool)digitalRead(D6);
  if (x != button_status)
  {
    button_status = x;
    Serial.print("Button: ");
    Serial.println(button_status);
    if(x == false)
    {
      digitalWrite(D7,LOW);
      digitalWrite(D1,HIGH);
    }
    else
    {
      digitalWrite(D7,HIGH);
      digitalWrite(D1,LOW);
    }
  }
  
}

void getFirebaseData(){  
  FirebaseObject obj = Firebase.get("rooms");
  if (Firebase.failed() != true)
  {
	  bool led1 = obj.getBool("kichen_room");
	  if (firstTime == true) {
		  firstTime = false;
		  l1 = led1;
		  digitalWrite(D7, !l1);
		  digitalWrite(D1, l1);
		  Serial.print("Led1:");
		  Serial.println(led1);
	  }
	  else {
		  if (l1 != led1) {
			  Serial.print("Led1:");
			  Serial.println(led1);
			  l1 = led1;
			  digitalWrite(D7, !l1);
			  digitalWrite(D1, l1);
		  }
	  }
  }
  else
  {
    Serial.println("Reading Fail");
  }
}

void loop() {
  //getInput();
  getFirebaseData();

  delay(500);
}


