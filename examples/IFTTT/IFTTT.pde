#include <Ppop.h>

Ppop ppop("{WIFINAME}", "{WIFIPASSWORD}");

void setup()
{
  ppop.wifiConnect(5000);
  Serial.begin(115200);

  String response;
  ppop.postOneIntToIFTTT( "{EventName}"  , "{ServiceKey}", 10, response);
  Serial.println(response);
  Serial.println("=======");
  
  ppop.postOneFloatToIFTTT( "{EventName}"  , "{ServiceKey}", 25.5, response);
  Serial.println(response);
  Serial.println("xxxxxxxx");

  ppop.postOneStringToIFTTT("{EventName}"  , "{ServiceKey}", "TEST Message", response);
  Serial.println(response);
  Serial.println("xxxxxxxx");


}

void loop()
{
  
}

