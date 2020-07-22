#include <ESP8266WiFi.h>
#include <Servo.h>
const char *ssid =  " "; //enter your wifi name     
const char *pass =  " ";//enter your wifi password
WiFiServer server(80);
int led = D7;
int fan = D3; 
Servo door;
void setup() 
{
       Serial.begin(9600);
       delay(10);
               
       Serial.println("Connecting to ");
       Serial.println(ssid); 
 
       WiFi.begin(ssid, pass); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
      Serial.println("");
      Serial.println("WiFi connected"); 
      // Start the server
      server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.println(WiFi.localIP());
  pinMode(fan, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(fan, HIGH);
  digitalWrite(led, HIGH);
  Serial.println("STARTED");
  door.attach(D6);
  door.writeMicroseconds(1250);
     
}
 
void loop() 
{      
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  if(client.available() > 0){
    client.flush();
    client.stop();
    return ;
  }
  

  String req = client.readStringUntil('\r');
  Serial.println(req);
  
  int val;
  if (req.indexOf("light0") != -1)
   { 
   
      digitalWrite(led, HIGH);
      Serial.println("led off");
    }
  else if (req.indexOf("light1") != -1)
    {
      digitalWrite(led, LOW);
      Serial.println("led on");
      
    
    }
    if (req.indexOf("fan0") != -1)
   { 
   
      digitalWrite(fan, HIGH);
      Serial.println("fan off");
    }
  else if (req.indexOf("fan1") != -1)
    {
      digitalWrite(fan, LOW);
      Serial.println("fan on");
      
    
    }
    if (req.indexOf("door0") != -1)
   {    door.writeMicroseconds(1150);
      
      Serial.println("door close");
    }
  else if (req.indexOf("door1") != -1)
    {
      door.writeMicroseconds(2000);
      Serial.println("door open");  
    }
    


  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now </html>";
  client.println(s);
    
  client.flush();
 
  client.stop();
}
