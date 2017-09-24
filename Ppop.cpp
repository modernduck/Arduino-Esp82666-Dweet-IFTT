/*
  Ppop.cpp - Library for make you life easy in cubic inno camp
  Created by Sompop Kulapalanont, May 4, 2017.
  Released into the public domain.
*/


#include "Ppop.h"
#include <ESP8266WiFi.h>
//#include <WiFiClientSecure.h>
// Config connect WiFi
#define WIFI_SSID "CUBIC-YELLOW"
#define WIFI_PASSWORD ""
WiFiClientSecure client;

Ppop::Ppop(char*  _ssd, char*  _password)
{
  
  ssd = _ssd;
  password = _password;
}

void Ppop::wifiConnect(int interval){
    WiFi.mode(WIFI_STA);
    // connect to wifi.
    WiFi.begin(ssd, password);
    while (WiFi.status() != WL_CONNECTED) {
        
        delay(interval);
    }
}


void Ppop::requestWeb(char* host, char* path, int port, int interval, String &payload) {
  if (!client.connect(host,port)) {
    //Serial.println("connection failed");
    return;   
  }
  String req = "";
  req += "GET ";
  req += path;
  req += " HTTP/1.1\r\n";
  req += "Host: ";
  req += host;
  req += "\r\n";
  req += "Connection: keep-alive\r\n";
  req += "\r\n";
 
  // Serial.println(req);
  client.print(req);
unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > interval) {
   //   Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  payload = "";
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    payload.concat(line);
    
  }
  
}

void Ppop::saveDweet(String dweet, String key, int value, String &payload){
  if (!client.connect("dweet.io" ,443)) {
    //Serial.println("connection failed");
    return;   
  }

  String info = "{";
  info += "\"";
  info += key;
  info += "\":";
  info += value;
  info += "}";
  
  String req = "";
  req += "POST ";
  req += "/dweet/for/" + dweet;
  req += " HTTP/1.1\r\n";
  req += "Host: ";
  req += "dweet.io";
  req += "\r\n";
  req += "Content-Length: ";
  req += info.length();
  req += "\r\n";
  req += "Content-Type: application/json\r\n";
  req += "Connection: keep-alive\r\n";
  req += "\r\n";
  req += info;
 
   Serial.println(req);
  client.print(req);
unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
   //   Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  payload = "";
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    payload.concat(line);
    
  }
}

void Ppop::saveDweetFloat(String dweet, String key, float value, String &payload){
  if (!client.connect("dweet.io" ,443)) {
    //Serial.println("connection failed");
    return;   
  }

  String info = "{";
  info += "\"";
  info += key;
  info += "\":";
  info += value;
  info += "}";
  
  String req = "";
  req += "POST ";
  req += "/dweet/for/" + dweet;
  req += " HTTP/1.1\r\n";
  req += "Host: ";
  req += "dweet.io";
  req += "\r\n";
  req += "Content-Length: ";
  req += info.length();
  req += "\r\n";
  req += "Content-Type: application/json\r\n";
  req += "Connection: keep-alive\r\n";
  req += "\r\n";
  req += info;
 
   Serial.println(req);
  client.print(req);
unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
   //   Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  payload = "";
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    payload.concat(line);
    
  }
}



void Ppop::getDweetJSON(String dweet, String &content){
  String path = "/get/latest/dweets/for/";
  path.concat(dweet);
  char *cstr = new char[path.length() + 1];
  strcpy(cstr, path.c_str());
  Ppop::requestWeb("dweet.io", cstr , 443, 5000, content);
  
}

void Ppop::parseJsonInt(String json, String key, int &value){
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  Serial.println(json);
  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }
  
  value = (int) root["with"][0]["content"][key];
}

void Ppop::parseJsonFloat(String json, String key, float &value){
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }
  
  value = (int) root["with"][0]["content"][key];
}

void Ppop::getDweetInt(String dweet, String key , int &payload){
  //wait 1 sec before call
  delay(2000);
  if (!client.connect("dweet.io" ,443)) {
    //Serial.println("connection failed");
    return;   
  }

  String path = "/get/latest/dweets/for/";
  path.concat(dweet);
  String req = "";
  req += "GET ";
  req += path;
  req += " HTTP/1.1\r\n";
  req += "Host: ";
  req += "dweet.io";
  req += "\r\n";
  req += "Connection: keep-alive\r\n";
  req += "\r\n";
 
   Serial.println(req);
  client.print(req);
unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
   //   Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  String json = "";
  // Read all the lines of the reply from server and print them to Serial
  int a =0;
  while(client.available()){
    String line = client.readStringUntil('\r');
    if(a > 6)
      json.concat(line);
    a++;
  }
Serial.print(json);
  Ppop::parseJsonInt( json,  key,  payload);

}

void Ppop::getDweetFloat(String dweet, String key , float &payload){
  //wait 1 sec before call
  delay(2000);
  if (!client.connect("dweet.io" ,443)) {
    //Serial.println("connection failed");
    return;   
  }

  String path = "/get/latest/dweets/for/";
  path.concat(dweet);
  String req = "";
  req += "GET ";
  req += path;
  req += " HTTP/1.1\r\n";
  req += "Host: ";
  req += "dweet.io";
  req += "\r\n";
  req += "Connection: keep-alive\r\n";
  req += "\r\n";
 
  // Serial.println(req);
  client.print(req);
unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
   //   Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  String json = "";
  // Read all the lines of the reply from server and print them to Serial
   int a =0;
  while(client.available()){
    String line = client.readStringUntil('\r');
    if(a > 6)
      json.concat(line);
    a++;
  }
  Serial.println(json);
  Ppop::parseJsonFloat( json,  key,  payload);

}




void Ppop::postOneIntToIFTTT(String name,String key,  int value, String &response){


  String path = "/trigger/";
  path.concat(name);
  path.concat("/with/key/");
  path.concat(key);
  path.concat("?value1=");
  path.concat(value);
  
  char *cstr = new char[path.length() + 1];
  strcpy(cstr, path.c_str());
  Serial.println(cstr);
  Ppop::requestWeb("maker.ifttt.com", cstr, 443, 5000, response);
}

void Ppop::postOneFloatToIFTTT(String name,String key,  float value, String &response){


  String path = "/trigger/";
  path.concat(name);
  path.concat("/with/key/");
  path.concat(key);
  path.concat("?value1=");
  path.concat(value);
  
  char *cstr = new char[path.length() + 1];
  strcpy(cstr, path.c_str());
  Serial.println(cstr);
  Ppop::requestWeb("maker.ifttt.com", cstr, 443, 5000, response);
}


void Ppop::postOneStringToIFTTT(String name,String key,  char* value, String &response){


  String path = "/trigger/";
  path.concat(name);
  path.concat("/with/key/");
  path.concat(key);
  path.concat("?value1=");
  path.concat(value);
  
  char *cstr = new char[path.length() + 1];
  strcpy(cstr, path.c_str());
  Serial.println(cstr);
  Ppop::requestWeb("maker.ifttt.com", cstr, 443, 5000, response);
}





/*
void Ppop::saveDweetInt(String dweet, String key, int value, String &payload){
  if (!client.connect(host,port)) {
    //Serial.println("connection failed");
    return;   
  }
  String req = "";
  req += "POST ";
  req += path;
  req += " HTTP/1.1\r\n";
  req += "Host: ";
  req += host;
  req += "\r\n";
  req += "Connection: keep-alive\r\n";
  req += "\r\n";
 
  // Serial.println(req);
  client.print(req);
unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > interval) {
   //   Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  payload = "";
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    payload.concat(line);
    
  }

}
*/