
#include "mlabSwitch.h"
MlabSwitch mSwitch;
void setup() {
  // put your setup code here, to run once:
	mSwitch.initWifi();
	mSwitch.initIO(D7, D1, D6);
	mSwitch.initFirebase("iotdev-6b58b.firebaseio.com","5zg8yd7bazlRj0heqBZvrduyyjykvshtRPCbjlYh");

}

void loop() {
  // put your main code here, to run repeatedly:
	mSwitch.Run();

}
