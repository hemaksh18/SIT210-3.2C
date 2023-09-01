#include <ESP8266Webhook.h>
#include <WiFiNINA.h>

char ssid[] = POCO PHONE;
char pass[] = dudeperfect;

WiFiClient client;

char  HOST[] = "maker.ifttt.com";
String PATH  = "/trigger/light_intense/with/key/o23qy_6nygdJ6_ICx0FoZ5H_bErkCt54b2t4fniQJAd"; 
String query = "?value1>=450&value2>=750";

void setup() {
  WiFi.begin(ssid, pass);

  Serial.begin(9600);
  while (!Serial);

  // connect to web server on port 80:
  if (client.connect(HOST, 80)) {

    Serial.println("Connected ");
  }
  else {
    Serial.println("connection failed");
  }
}

void loop() {
  if (Serial.read() == 'r') {

    
    client.println("GET " + PATH+ query + " HTTP");
    client.println("Host: " + String(HOST));
    client.println("Connection: close");
    client.println();

    int Value = analogRead(A0);

    Serial.print("reading: ");
    Serial.print(Value);   



    while (client.connected()) {
      if (client.available()) {
        
        char read = client.read();
        Serial.print(read);

        if (Value < 10) {
        Serial.println(" - very Dark");
        delay(2000);
        } 
        else if (Value < 350) {
        Serial.println(" - Dark");
        delay(2000);
        } 
        else if (Value < 450) {
        Serial.println(" - Bright");
        delay(2000);
        } 
        else if (Value < 750) {
        Serial.println(" - Brighter");
        delay(2000);
        } 
        else {
        Serial.println(" -brightest");
        delay(2000);
        }
                   
      }
    }
    delay(500);
  }
    
  client.stop();
  Serial.println();
  Serial.println("disconnected");
}

