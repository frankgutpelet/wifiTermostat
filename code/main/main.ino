#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <TimerEvent.h>
#include "base.hpp"
#include "Logger.hpp"
#include "OneWire.h"
#include <DallasTemperature.h>
#include "Save.hpp"
#include "regulator.hpp"
#include <DNSServer.h>


const char* ssid = "LueftungKuehlschrank";
const char* password = ".ubX54bVSt#vxW11m.";
const char* myhostname = "LueftungKuehlschrank";

const char* title = "Temperatursteuerung";
const unsigned int timerOnePeriod = 1000;
double tempMax;
double tempMin;
double lastTemp = 0.0;
int relaisPin = 16; //D0 @ nodeMCU
regulator tempRegulator(0,0,0,0,0);
String fwVersion = "Version 1.1";
ESP8266WebServer server(80);
base indexPage(&server);
Logger* logger = Logger::instance();
TimerEvent timerOne;
bool relStatus = false;
SaveEEprom storage;
const byte DNS_PORT = 53;
DNSServer dnsServer;

OneWire oneWire(4); //D2 @ nodeMCU
DallasTemperature sensors(&oneWire);

void handleSubmit() 
{
 
  if (String("") != indexPage.Get_outSetTempMax())
  {
    double tempMax = indexPage.Get_outSetTempMax().toDouble();
    storage.Set_tempMax(tempMax);
    indexPage.Set_outSetTempMax("");
    tempRegulator.setTempMax(tempMax);
  }
  else if (String("") != indexPage.Get_outSetTempMin())
  {
    double tempMin = indexPage.Get_outSetTempMin().toDouble();
    storage.Set_tempMin(tempMin);
    indexPage.Set_outSetTempMin("");
    tempRegulator.setTempMin(tempMin);
  }
  else if (String("") != indexPage.Get_outTreshold())
  {
    double treshold = indexPage.Get_outTreshold().toDouble();
    Serial.println(indexPage.Get_outTreshold() + " double: " + treshold);
    storage.Set_treshold(treshold);
    tempRegulator.setTreshold(treshold);
  }
  else if (String("") != indexPage.Get_outCalibrate())
  {
    storage.Set_calibrate(indexPage.Get_outCalibrate().toDouble());
    indexPage.Set_outCalibrate("");
  }
  Render();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void Render()
{
  indexPage.Set_headline(String(title) + " - " + myhostname);
  indexPage.Render();
}

void sendTemp()
{
  server.send(200, "text/plain", indexPage.Get_temp());
}

void setup(void) {
  Serial.begin(115200);

  // Access Point Modus
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.println("Access Point gestartet");
  Serial.print("SSID: "); Serial.println(ssid);
  Serial.print("IP-Adresse: "); Serial.println(WiFi.softAPIP());
  // DNS auf ESP-IP umleiten
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  sensors.begin();

  server.on("/", Render);
  server.on("/temp", sendTemp);
  server.onNotFound([]() {
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
  });
  indexPage.SetCallback_submit(handleSubmit); 

  server.begin();
  Serial.println("HTTP server gestartet");

  timerOne.set(timerOnePeriod, timerOneFunc);
  indexPage.Set_headline(String(title) + " - " + myhostname);
  indexPage.Set_version(fwVersion);
  pinMode(relaisPin, OUTPUT);

  tempRegulator.setTempMin(storage.Get_tempMin());
  tempRegulator.setTempMax(storage.Get_tempMax());
  tempRegulator.setTreshold(storage.Get_treshold());
}


void loop(void) {
  server.handleClient();
  timerOne.update();
  dnsServer.processNextRequest();
}

void timerOneFunc()
{
  double temp = 0.0;
  double treshold = 0.0;
  double tempMin = 0.0;
  double tempMax = 0.0;
  String tempString = "";
  
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0) + storage.Get_calibrate();
  if (-50.0 < temp)
  {
    lastTemp = temp;
  }


  treshold = storage.Get_treshold();
  //Serial.println(String(indexPage.Get_outSetTempMax()) + "°C");
  //Serial.println(String(indexPage.Get_outSetTempMin()) + "°C");
   
  tempString = String(temp);
  //tempString = tempString.substring(tempString.length() - 2);
  indexPage.Set_temp(tempString);  
  tempMax= storage.Get_tempMax();
  tempMin= storage.Get_tempMin();
  indexPage.Set_setTempMax(String(tempMax));
  indexPage.Set_setTempMin(String(tempMin));
  indexPage.Set_calibrate(String(storage.Get_calibrate()));
  indexPage.Set_treshold(String(storage.Get_treshold()));


  relStatus = tempRegulator.isOn(lastTemp, true);
  
  if (relStatus)
  {
    indexPage.Set_status("ON");
    digitalWrite(relaisPin, HIGH);
  }
  else
  {
    indexPage.Set_status("OFF");
    digitalWrite(relaisPin, LOW);
  }
}
