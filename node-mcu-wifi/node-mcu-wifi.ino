#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define INA1  15          // L298N in1 motors Right           GPIO13(D7)
#define INA2  13          // L298N in2 motors Right           GPIO15(D8)
#define INB1  0           // L298N in3 motors Left            GPIO0(D3)
#define INB2  2           // L298N in4 motors Left            GPIO2(D4)

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff=1;

ESP8266WebServer server(80);      // Create a webserver object that listens for HTTP request on port 80

const char* ssid = "PJ";
const char *password = "1234567890";

WiFiClient client;

void connectToWiFi() {
//Connect to WiFi Network
   Serial.println();
   Serial.println();
   Serial.print("Connecting to WiFi");
   Serial.println("...");
   WiFi.begin(ssid, password);
   int retries = 0;
while ((WiFi.status() != WL_CONNECTED) && (retries < 15)) {
   retries++;
   delay(500);
   Serial.print(".");
}
if (retries > 14) {
    Serial.println(F("WiFi connection FAILED"));
}
if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi connected!"));
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
    Serial.println(F("Setup ready"));
}

void setup() {
 Serial.begin(115200);
 connectToWiFi();
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT); 
  
 pinMode(INA1, OUTPUT);
 pinMode(INA2, OUTPUT);
 pinMode(INB1, OUTPUT);
 pinMode(INB2, OUTPUT); 
 
 
  
// Connecting WiFi
   
}

void goAhead(){ 

      analogWrite(ENA, speedCar*speed_Coeff);    //enable(ENA) and speed 0-255
      analogWrite(ENB, speedCar*speed_Coeff);

      digitalWrite(INA1, LOW);
      digitalWrite(INA2, HIGH);

      digitalWrite(INB1, HIGH);
      digitalWrite(INB2, LOW);
      
  }

void goBack(){ 

      analogWrite(ENA, speedCar*speed_Coeff);    //enable(ENA) and speed 0-255
      analogWrite(ENB, speedCar*speed_Coeff);
      

      digitalWrite(INA1, HIGH);
      digitalWrite(INA2, LOW);

      digitalWrite(INB1, LOW);
      digitalWrite(INB2, HIGH);   
  }

void goRight(){ 

      analogWrite(ENA, speedCar*speed_Coeff);    //enable(ENA) and speed 0-255
      analogWrite(ENB, speedCar*speed_Coeff);
     
      digitalWrite(INA1, LOW);
      digitalWrite(INA2, HIGH);

      digitalWrite(INB1, LOW);
      digitalWrite(INB2, HIGH);

          

  }

void goLeft(){

      analogWrite(ENA, speedCar*speed_Coeff);    //enable(ENA) and speed 0-255
      analogWrite(ENB, speedCar*speed_Coeff);
     
      
      digitalWrite(INA1, HIGH);
      digitalWrite(INA2, LOW);

      digitalWrite(INB1, HIGH);
      digitalWrite(INB2, LOW);

         
  }
/*
void goAheadRight(){
      
      analogWrite(ENA, speedCar*speed_Coeff);    //enable(ENA) and speed 0-255
      analogWrite(ENB, speedCar*speed_Coeff);
      analogWrite(ENC, speedCar*speed_Coeff);      //Rear wheel does not need to rotate
      
      digitalWrite(INA1, LOW);
      digitalWrite(INA2, HIGH);
      digitalWrite(INB1, LOW);
      digitalWrite(INB2, HIGH);
      digitalWrite(INC1, HIGH);
      digitalWrite(INC2, LOW);      
   }
void goAheadLeft(){
      
      analogWrite(ENA, speedCar*speed_Coeff);    //enable(ENA) and speed 0-255
      analogWrite(ENB, speedCar*speed_Coeff);
      analogWrite(ENC, speedCar*speed_Coeff);      //Rear wheel does not need to rotate
      
      digitalWrite(INA1, HIGH);
      digitalWrite(INA2, LOW);
      digitalWrite(INB1, HIGH);
      digitalWrite(INB2, LOW);
      digitalWrite(INC1, LOW);
      digitalWrite(INC2, HIGH);      
  }
void goBackRight(){ 
      
  }
void goBackLeft(){ 
     
  }
*/
void stopRobot(){  

      analogWrite(ENA, 0);    //enable(ENA) and speed 0-255
      analogWrite(ENB, 0);
      
 }

void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
     /* else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "0") speedCar = 400;
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023; */
      else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
