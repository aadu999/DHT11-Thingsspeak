#include<Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#define DHTPIN 2 
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);  
float temperature, humidity; 
ESP8266WiFiMulti WiFiMulti;

void setup() {
  // put your setup code here, to run once:
 dht.begin();
 Serial.begin(115200);
   WiFiMulti.addAP("Nadata", "");
}

void loop() {
  // put your main code here, to run repeatedly:
  temperature = dht.readTemperature();  
  humidity = dht.readHumidity(); 
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%");  
  delay(1000);
   if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;
        http.begin("http://api.thingspeak.com/update?api_key=JLAESJCD7EEFXMYZ&field1="+String(temperature)+"&field2="+String(humidity));
        if(http.GET()==HTTP_CODE_OK)
        {
          Serial.println("Data Send");
        }
        http.end();
        }
}
