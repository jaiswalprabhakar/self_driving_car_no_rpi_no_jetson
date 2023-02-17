#define ENA 14  // Enable/speed motors Right        GPIO14(D5)
#define ENB 12  // Enable/speed motors Left         GPIO12(D6)
#define INA1 15 // L298N in1 motors Right           GPIO13(D7)
#define INA2 13 // L298N in2 motors Right           GPIO15(D8)
#define INB1 0  // L298N in3 motors Left            GPIO0(D3)
#define INB2 2  // L298N in4 motors Left            GPIO2(D4)

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

String command;     // String to store app command state.
int speedCar = 800; // 400 - 1023.
int speed_Coeff = 1;

const char *ssid = "Make DIY";
ESP8266WebServer server(80);

void setup()
{

    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(INA1, OUTPUT);
    pinMode(INA2, OUTPUT);
    pinMode(INB1, OUTPUT);
    pinMode(INB2, OUTPUT);

    Serial.begin(115200);

    // Connecting WiFi

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    // Starting WEB-server
    server.on("/", HTTP_handleRoot);
    server.onNotFound(HTTP_handleRoot);
    server.begin();
}

void goAhead()
{

    analogWrite(ENA, speedCar * speed_Coeff); // enable(ENA) and speed 0-255
    analogWrite(ENB, speedCar * speed_Coeff);

    digitalWrite(INA1, LOW);
    digitalWrite(INA2, HIGH);

    digitalWrite(INB1, HIGH);
    digitalWrite(INB2, LOW);
}

void goBack()
{

    analogWrite(ENA, speedCar * speed_Coeff); // enable(ENA) and speed 0-255
    analogWrite(ENB, speedCar * speed_Coeff);

    digitalWrite(INA1, HIGH);
    digitalWrite(INA2, LOW);

    digitalWrite(INB1, LOW);
    digitalWrite(INB2, HIGH);
}

void goRight()
{

    analogWrite(ENA, speedCar * speed_Coeff); // enable(ENA) and speed 0-255
    analogWrite(ENB, speedCar * speed_Coeff);

    digitalWrite(INA1, HIGH);
    digitalWrite(INA2, LOW);

    digitalWrite(INB1, HIGH);
    digitalWrite(INB2, LOW);
}

void goLeft()
{

    analogWrite(ENA, speedCar * speed_Coeff); // enable(ENA) and speed 0-255
    analogWrite(ENB, speedCar * speed_Coeff);

    digitalWrite(INA1, LOW);
    digitalWrite(INA2, HIGH);

    digitalWrite(INB1, LOW);
    digitalWrite(INB2, HIGH);
}

void stopRobot()
{

    analogWrite(ENA, 0); // enable(ENA) and speed 0-255
    analogWrite(ENB, 0);
    digitalWrite(INA1, LOW);
    digitalWrite(INA2, LOW);
    digitalWrite(INB1, LOW);
    digitalWrite(INB2, LOW);
}

void loop()
{
    server.handleClient();

    command = server.arg("State");
    if (command == "F")
        goAhead();
    else if (command == "B")
        goBack();
    else if (command == "L")
        goLeft();
    else if (command == "R")
        goRight();
    /* else if (command == "I") goAheadRight();
     else if (command == "G") goAheadLeft();
     else if (command == "J") goBackRight();
     else if (command == "H") goBackLeft(); */
    else if (command == "0")
        speedCar = 200;
    else if (command == "1")
        speedCar = 300;
    else if (command == "2")
        speedCar = 400;
    else if (command == "3")
        speedCar = 500;
    else if (command == "4")
        speedCar = 600;
    else if (command == "5")
        speedCar = 700;
    else if (command == "6")
        speedCar = 800;
    else if (command == "7")
        speedCar = 900;
    else if (command == "8")
        speedCar = 1000;
    else if (command == "9")
        speedCar = 1023;
    else if (command == "S")
        stopRobot();
}

void HTTP_handleRoot(void)
{

    if (server.hasArg("State"))
    {
        Serial.println(server.arg("State"));
    }
    server.send(200, "text/html", "");
    delay(1);
}