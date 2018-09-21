#define RST_PIN         D1
#define SS_PIN          D8
#define USERNAME "mohdm2611"
#define DEVICE_ID "esp8266_rfid"
#define DEVICE_CREDENTIAL "some_credentials"
#include<ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
const char* host = "dev57849.service-now.com";
const int httpsPort = 443;
#define red 2
#define green 16
char ssid[] = "AndroidAP";  //  your network SSID (name)
char pass[] = "clvi1477";       // your network password D-Link_DIR-600M
unsigned int g_connectionCounter = 1;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
//ThingerESP8266 *thing;
void setup()
{
  Serial.begin(115200);   // Initiate a serial commun  ation
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
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
  // thing =  new ThingerESP8266(USERNAME,DEVICE_ID,DEVICE_CREDENTIAL);
  /*(*thing)["user_id"] >> [] (pson& out){
  String user_id = "mohdm2611@gmail.com";
  String module_id = "F9 BA A5 2B";
  out = user_id;
  out = module_id;
};
(*thing)["module_id"] >> [] (pson& out){
float distance;
getDistancevalue(distance);
out = distance;
};*/
}
void loop()
{
  // //(*thing).handle();
  // // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
   return;
  }
   // Select one of the cards
   if ( ! mfrc522.PICC_ReadCardSerial())
   {
     return;
   }
   //Show UID on serial monitor
   Serial.println();
   Serial.print(" UID tag :");
   String content= "";
   byte letter;
   for (byte i = 0; i < mfrc522.uid.size; i++)
   {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
   }
   content.toUpperCase();
   Serial.println();
   if (content.substring(1) == "F9 BA A5 2B") //change UID of the card that you want to give access
   {
    String module_id, user_id;
    user_id = "mohdm2611@gmail.com";
    module_id = "F9 BA A5 2B";
    Serial.println(" Access Granted ");
    Serial.println(module_id);
     delay(1000);
  if(pushValue(user_id,module_id)){
    Serial.println("Successfull");
  }
  else{
    Serial.println("Sorry!!");
  }
  delay(5000);
}
bool pushValue(String user_id, String module_id) {
  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  if (!client.connect(host, httpsPort) || (WiFi.status() != WL_CONNECTED)) {
    Serial.println("HTTPS Connect Failed ");
    return false;
  }
  String url = "/api/x_269723_steck/module_check";
  String jsonContent = "{'user_id':'"+ String(user_id) +"','module_id':'"+ String(module_id) + "','length':'"+ 50 + "'}\r\n";
  Serial.print("Sending value to service now : ");
  Serial.println(jsonContent);
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" +
  "User-Agent: ESP8266\r\n" +
  "Content-Type: application/json\r\n" +
  "Accept: application/json\r\n" +
  "Authorization: Basic YWRtaW46ZkByaGFuU2VydmljZW4wdw==\r\n"+
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
  Serial.println("Successfully posted values to ServiceNow instance ... ");
  String json="";
  json += (client).readStringUntil('\n');
  while (client.connected() && client.available()) {
    // First read body length
    String bodyLengthLine = (client).readStringUntil('\n');
    int bodyLength = bodyLengthLine.toInt();
    Serial.println(bodyLength);
    if(bodyLength == 0) {
      break;
    }
    Serial.println("Body Length - " + bodyLengthLine);
    json += (client).readStringUntil('\n');
  }
  Serial.println(json);
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root3 = jsonBuffer.parseObject(json);
  if (!root3.success()) {
    Serial.println("ERROR: parseObject() failed  1");
    return false;
  }
  JsonObject& result = root3["result"];
  String url2 = result["body"];
  return true;
}

