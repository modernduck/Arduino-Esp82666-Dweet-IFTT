/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#ifndef Ppop_h
#define Ppop_h


#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

class Ppop
{
  public:
    Ppop(char*  ssd, char*  password);
    void wifiConnect(int interval);
    void requestWeb(char* host, char* path, int port, int interval, String &payload);
    void postOneIntToIFTTT(String name,String key,  int value, String &response);
    void postOneFloatToIFTTT(String name,String key,  float value, String &response);
    void getDweetJSON(String dweet, String &content);
    void saveDweet(String dweet, String key, int value, String &payload);
    void parseJsonInt(String json, String key, int &value);
    void getDweetInt(String dweet, String key , int &payload);
  private:
    int _pin;
    char*  ssd;
    char*  password;
};

#endif

