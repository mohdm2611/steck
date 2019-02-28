#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "mohdm2611"
#define DEVICE_ID "esp8266"
#define DEVICE_CREDENTIAL "some_credentials"

char ssid[] = "AndroidAP";  //  your network SSID (name)
char pass[] = "clvi1477";       // your network password D-Link_DIR-600M

const int trigPin = 12;  //D6
const int echoPin = 13;  //D7

const char* host = "dev57849.service-now.com";
const int httpsPort = 443;

bool getDistanceValues(float&);

unsigned long int t_SENSE_TEMP = 0;
unsigned long int t_DISPLAY_DELAY = 0;
unsigned long int t_FLASH = 0;

unsigned int g_connectionCounter = 1;

//ThingerESP8266 *thing;
void setup(){
 // thing.add_wifi(SSID, SSID_PASSWORD);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
    if(g_connectionCounter) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: "); 
    Serial.println(WiFi.localIP());
  }
 //thing =  new ThingerESP8266(USERNAME,DEVICE_ID,DEVICE_CREDENTIAL);

  //(*thing)["SONIC"] >> [] (pson& out){
   // float distance;
    //getDistancevalue(distance);
   // out = distance;
 // };
  t_SENSE_TEMP = millis();
  t_FLASH = t_DISPLAY_DELAY = millis();
}
void loop() {

  float distance;

  // read the temperature & humidity
  
  //(*thing).handle();
  if(millis() - t_SENSE_TEMP > 12000) {

    if(getDistancevalue(distance)) {
      Serial.println(distance);
      if(pushValueToActive(distance, "esp8266")) {
         if(pushValueToTracker(distance, "esp8266")){
          Serial.println("Successfully posted to tracker table ...");
        }
        Serial.println("Successfully posted to active table ...");
      }
      else {
        Serial.println("Failed to post data to ServiceNow ! Check your internet connectivity ...");
      }
      Serial.print("Distance ");
      Serial.println(distance);

    } else {
      Serial.println("Unable to read Ultrasonic sensor data ");
    }
    t_SENSE_TEMP = millis();
  }

  if(millis() - t_FLASH > 500) {
    t_FLASH = millis();
  }

}
bool getDistancevalue(float &dist) {
  // read without samples.
  double duration;
  float distance;
   digitalWrite(trigPin, LOW);  // Get Start
    delayMicroseconds(2); // stable the line 
    digitalWrite(trigPin, HIGH); // sending 10 us pulse
    delayMicroseconds(10); // delay 
    digitalWrite(trigPin, LOW); // after sending pulse wating to receive signals 
    duration = pulseIn(echoPin, HIGH); // calculating time 
    distance= duration*0.034/2;
   // out = distance;
  dist = distance;

  Serial.print("Distance - ");
  Serial.println(dist);

  Serial.println();

  return true;
}
/*bool pushValueToThinger(float dist, String device_id){
  pson out;
  out["length"] = dist;
  (*thing).handle();
  if ((*thing).call_endpoint("distancedata", out) == 1) {
    Serial.println("Posted successfully ...");
    Serial.println("**ThingerManager: a posted to ServiceNow successfully via Thinger ");
    return true;
  }
  Serial.println("Failed to post data ...");
  return false;
}*/
bool pushValueToActive(float distance, String device_id) {

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
 if (!client.connect(host, httpsPort) || (WiFi.status() != WL_CONNECTED)) {
   return false;
  }

  String url = "/api/x_269723_steck/ultrasonic_data";
  String moduleid = "F9 BA A5 2B";
  String jsonContent = "{'module_id':'"+ moduleid +"','value':'"+ String(distance) +"'}\r\n";

  Serial.print("Sending value to service now : ");
  Serial.println(jsonContent);

  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Content-Type: application/json\r\n" +
               "Accept: application/json\r\n" +
               "Authorization: Basic YWRtaW46ZkByaGFuU2VydmljZW4wdw==\r\n" +
               "Content-Length: " + jsonContent.length() + "\r\n" +
               "Connection: close\r\n\r\n" +
               jsonContent);

  //  bypass HTTP headers
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println( "Header: " + line );
    if (line == "\r") {
      break;
    }
  }
  //  read body length
  int bodyLength = 0;
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    bodyLength = line.toInt();
    break;
  }

  Serial.println("Successfully posted values to module active table ... ");

  return true;

}
bool pushValueToTracker(float distance, String device_id) {

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
 if (!client.connect(host, httpsPort) || (WiFi.status() != WL_CONNECTED)) {
   return false;
  }

  String url = "/api/x_269723_steck/ultrasonic_tracker";
  String moduleid = "F9 BA A5 2B";
  String jsonContent = "{'module_id':'"+ moduleid +"','value':'"+ String(distance) +"'}\r\n";

  Serial.print("Sending value to service now : ");
  Serial.println(jsonContent);

  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Content-Type: application/json\r\n" +
               "Accept: application/json\r\n" +
               "Authorization: Basic YWRtaW46ZkByaGFuU2VydmljZW4wdw==\r\n" +
               "Content-Length: " + jsonContent.length() + "\r\n" +
               "Connection: close\r\n\r\n" +
               jsonContent);

  //  bypass HTTP headers
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println( "Header: " + line );
    if (line == "\r") {
      break;
    }
  }
  //  read body length
  int bodyLength = 0;
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    bodyLength = line.toInt();
    break;
  }

  Serial.println("Successfully posted values tracker table ... ");

  return true;
}

