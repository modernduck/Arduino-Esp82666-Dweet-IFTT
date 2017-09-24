# Arduino-Esp82666-Dweet-IFTT



# เริ่มต้นการใช้งาน

1. ) Include Library <br/>
`#include <Ppop.h>`

2. ) Set การเชื่อมต่อด้วย <br/>
`Ppop ppop("{WIFINAME}", "{WIFIPASSWORD}");`<br/>
แทนค่า {WIFINAME} ด้วย ชื่อ Wifi ที่จะเชื่อมต่อ ส่วน {WIFIPASSWORD} คือรหัสของ Wifi<br/>

3. ) ทำการเชื่อมต่อ Wifi ด้วย <br/>
`ppop.wifiConnect(5000)`<br/>
จะทำการเชือ่มต่อ Wifi จนกว่าจะต่อติดทุก 5 วินาที (เปลี่ยนค่า 5000 เป็นค่าอื่นได้) <br/>

# ทำการส่งข้อมูลให้ IFTTT

คำส่งที่เราเตรียมไว้ให้มี 3 คำส่งคือ<br/>

1. ) postOneIntToIFTTT(String name,String key,  int value, String &response);
2. ) postOneFloatToIFTTT(String name,String key,  float value, String &response);
3. ) postOneStringToIFTTT(String name,String key,  char* value, String &response);
<p>
โดย name ต้องแทนค่าด้วย ด้วย ชื่อ Event ของ IFTTT ส่วน key แทนค่าด้วย key ของ บริการ Webhook
</p>
ตัวอย่างการใช้งาน
<pre>
  String response;
  ppop.postOneIntToIFTTT( "{EventName}"  , "{ServiceKey}", 10, response);</pre>
 
จะทำการส่ง 10 ไปให้ {EventName} ของ IFTTT โดยเก็บผลลัพท์ไว้ใน response เพื่อที่จะทำให้เราสามารถเชคได้

# ทำการส่งข้อมูลให้ Dweet

1. ) saveDweet(String dweet, String key, int value, String &payload);
2. ) saveDweetFloat(String dweet, String key, float value, String &payload);
3. ) getDweetInt(String dweet, String key , int &payload);
4. ) getDweetFloat(String dweet, String key , float &payload);
