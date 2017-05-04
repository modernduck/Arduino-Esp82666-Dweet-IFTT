#include <Ppop.h>

Ppop ppop("CUBIC-YELLOW", "");

void setup()
{
  ppop.wifiConnect();
  Serial.begin(115200);
}

void loop()
{
  String payload;
  ppop.requestWeb("www.arduino.cc", "/asciilogo.txt", 443, 5000, payload);
  Serial.println("--from payload--");
  Serial.println(payload);
  Serial.println("--end payload --");
}

