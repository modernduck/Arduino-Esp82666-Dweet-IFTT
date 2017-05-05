#include <Ppop.h>

Ppop ppop("{WIFINAME}", "{WIFIPASSWORD}");


int cloudCount;
float cloudTemp;
void setup()
{
  ppop.wifiConnect(5000);
  Serial.begin(115200);

  String response;
  //save data to cloud
  ppop.saveDweet("ppop-cool", "temperature", 50, response);
  Serial.println(response);
  Serial.println("=======");
  
  //get data from cloud to INT
  
  ppop.getDweetInt("ppop-cool", "count" , cloudCount);

  Serial.println(response);
  Serial.println("xxxxxxxx");
  //get data from cloud to FLOAT
  ppop.getDweetFloat("ppop-cool", "temperature" , cloudTemp);

  Serial.println(response);
  Serial.println("xxxxxxxx");
}

void loop()
{
  
}

