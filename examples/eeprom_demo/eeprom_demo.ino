#include <EEPROM.h>
#include <ESP8266WiFi.h>
uint16_t count = 0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  if (WiFi.SSID().length() == 0)
  {
	  Serial.println("Start Smart Config because no saved ssid");
	  WiFi.mode(WIFI_STA);
	  delay(500);
	  WiFi.setAutoConnect(false);
	  WiFi.setAutoReconnect(false);
	  WiFi.beginSmartConfig();
  }
  else
  {
	  Serial.println("Connect Wifi base on saved ssid and psk");
	  WiFi.begin();
  }

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
	count++;
    Serial.print(".");
	if (count >= 10)
	{
		Serial.println("Nomal Connect Timeout, switch to smartConfig");
		break;
	}
  }
  if (count >= 10)
  {
	  Serial.println("Start Smart Config function");

	  WiFi.mode(WIFI_STA);
	  delay(500);
	  WiFi.setAutoConnect(false);
	  WiFi.beginSmartConfig();
	  while (WiFi.status() != WL_CONNECTED)
	  {
		  delay(500);
		  Serial.print(".");
	  }
	  WiFi.smartConfigDone();
	  Serial.println("");
	  Serial.println("WiFi connected");
	  Serial.println("IP address: ");
	  Serial.println(WiFi.localIP());
	  Serial.print("SSID:");
	  Serial.println(WiFi.SSID());
	  Serial.print("Psk:");
	  Serial.println(WiFi.psk());
	   
  }
  else
  {
	  Serial.println("WiFi connected");
	  Serial.println("IP address: ");
	  Serial.println(WiFi.localIP());
	  Serial.print("SSID:");
	  Serial.println(WiFi.SSID());
	  Serial.print("Psk:");
	  Serial.println(WiFi.psk());
  }

  

}

void loop() {
  // put your main code here, to run repeatedly:

}
