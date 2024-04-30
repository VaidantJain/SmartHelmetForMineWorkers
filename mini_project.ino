#include <DHT.h>
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include <PulseSensorPlayground.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>

#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define BUTTON 13
#define BUZZ 16

int status=0;
const char* ssid = "Meth_Lab 4G";
const char* password = "iambadboi";
unsigned long myChannelNumber = 2505402;
const char * myWriteAPIKey = "2MJV2GOE74JJZCTM";
const int pulsePin = A0;
int prev_button_state= HIGH;
int button_state;
WiFiClient  client;
PulseSensorPlayground pulseSensor;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  // Connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  pinMode(BUZZ,OUTPUT);
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
  pinMode(BUTTON,INPUT_PULLUP);
  pulseSensor.analogInput(pulsePin);

  pulseSensor.setThreshold(550);

  // Start the pulse sensor

  pulseSensor.begin();
}

void loop() {
  button_state=LOW;
  delay(200);  // Delay between sensor readings
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
 

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C"));
  button_state=digitalRead(BUTTON);
  //pulseSensor.update();
  int heartRate = pulseSensor.getBeatsPerMinute();
  

    Serial.println("Heart rate: " + String(heartRate) + " bpm");

   
  if(temperature>50 || humidity>100 || heartRate<40){
    digitalWrite(BUZZ,HIGH);
    delay(2000);
  }
  digitalWrite(BUZZ,LOW);

  if(prev_button_state==LOW && button_state==HIGH){
    Serial.println("State has changed");
  }
  prev_button_state=button_state;
  ThingSpeak.setField(1,temperature);
  ThingSpeak.setField(2,humidity);
  ThingSpeak.setField(3,heartRate);
  ThingSpeak.setField(4,button_state);
  int x = ThingSpeak.writeFields(myChannelNumber,  myWriteAPIKey);
  prev_button_state=LOW;
  // if(prev_button_state==HIGH){
  //   delay(2000);
  //   prev_button_state=LOW;
  //   button_state=LOW;
  // }
  //int y = ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey);
  if(x == 200 ){
      Serial.println("Channel update successful.");
    }
    
}