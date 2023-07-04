# BLYNK_TEMPLATE_ID "TMPLIOY3kvUU" 
#define BLYNK_DEVICE_NAME "NPD"
#define BLYNK_AUTH_TOKEN "MbSQCmgF3saysAsegGHG9Os52YSbPhN9"
#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "name"; // type your wifi name
char pass[] = "pass"; // type your wifi password
#define DHTPIN 12 // Mention the digital pin where you connected 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
void sendSensor(){
float h = dht.readHumidity();
float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit 
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!"); 
return;
}
float gas; 
gas=analogRead(A0);
Blynk.virtualWrite(V1, h); 
Blynk.virtualWrite(V0, t); 
Blynk.virtualWrite(V2, gas); 
Serial.print("Temperature : "); 
Serial.print(t);
Serial.print(" Humidity : "); 
Serial.print(h);
Serial.print(" Gas: "); 
Serial.println(gas);
if(t > 20 && gas>630){
// Blynk.email("jayantilaxmi5@gmail.com", "Alert", "Temperature over 28C!"); 
Blynk.logEvent("spoil_alert","The Food is Spoilt"); 
Blynk.virtualWrite(V3,"Food is Spoilt");
digitalWrite(5,HIGH);
35
digitalWrite(4,HIGH); 
delay(500); 
digitalWrite(5,LOW); 
digitalWrite(4,LOW);
}
else{
Blynk.virtualWrite(V3,"Food is safe to consume");
}
}
BLYNK_CONNECTED(){
Blynk.syncVirtual(V4);
}
BLYNK_WRITE(V4){
int pinvalue=param.asInt();
// Serial.print("Slider value is: ");
//
// Serial.println(pinvalue);
if(pinvalue==1){
Serial.println("The Device is ON");
// timer.setInterval(2500L, sendSensor); 
sendSensor();
}
else{
Serial.println("The Device is OFF");
}
}
void setup(){ 
Serial.begin(115200); 
Blynk.begin(auth, ssid, pass); 
pinMode(5,OUTPUT); 
pinMode(4,OUTPUT); 
dht.begin();
}
void loop(){ 
Blynk.run();
timer.run();
}