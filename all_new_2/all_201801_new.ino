#include "IRRecvCounter.h"
#include <Wire.h>
#include <SPI.h>

//大氣壓
#include "Seeed_BME280.h"

BME280 bme280;


//rain
int rainpin = 2;
int RR = 0;
float rainmeter = 0;

//wind
const int windPin = A0;
int windsensorValue = 0;
float windsensorVoltage = 0.0;
float windSpeed = 0.0;

//蟲罐
int g_nD5Pin = 5;
int g_nD6Pin = 6;
int g_nD7Pin = 7;
int g_nD8Pin = 8;
int g_nD9Pin = 9;
int g_nD10Pin = 10;
int g_nD11Pin = 11;
int g_nD12Pin = 12;
int g_nD13Pin = 13;
//int g_nA4Pin = A4;
//int g_nA5Pin = A5;

int timemeow = 100;

CIRRecvCounter g_IRRecvD5(g_nD5Pin, DEF_TYPE_DIGITAL);
CIRRecvCounter g_IRRecvD6(g_nD6Pin, DEF_TYPE_DIGITAL);
CIRRecvCounter g_IRRecvD7(g_nD7Pin, DEF_TYPE_DIGITAL);
CIRRecvCounter g_IRRecvD8(g_nD8Pin, DEF_TYPE_DIGITAL);
CIRRecvCounter g_IRRecvD9(g_nD9Pin, DEF_TYPE_DIGITAL);
CIRRecvCounter g_IRRecvD10(g_nD10Pin, DEF_TYPE_DIGITAL);
CIRRecvCounter g_IRRecvD11(g_nD11Pin, DEF_TYPE_DIGITAL);
CIRRecvCounter g_IRRecvD12(g_nD12Pin, DEF_TYPE_DIGITAL);
CIRRecvCounter g_IRRecvD13(g_nD13Pin, DEF_TYPE_DIGITAL);
//CIRRecvCounter g_IRRecvA4(g_nA4Pin, DEF_TYPE_ANALOG);
//CIRRecvCounter g_IRRecvA5(g_nA5Pin, DEF_TYPE_ANALOG);

//LED
bool LED_S = HIGH;

//土壤濕度FDS100
int mudhumpin = A1;

void setup() {
  Serial.begin(9600);
  //LED 開關
  pinMode(3,OUTPUT);
  //大氣壓
if(!bme280.init()){
    Serial.println("Device error!");
  }

  //土壤濕度FDS100
  pinMode(mudhumpin,INPUT);

  //rain
  pinMode( rainpin , INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(rainpin), blink, RISING);
}


void blink()//rain
{
  rainmeter += 0.2;
}

void loop() {
    //捕蟲罐1
     g_IRRecvD5.IRRecvCount(timemeow);
     long Count1 = g_IRRecvD5. getCount();

     g_IRRecvD6.IRRecvCount(timemeow);
     long Count2 = g_IRRecvD6. getCount();

     g_IRRecvD7.IRRecvCount(timemeow);
     long Count3 = g_IRRecvD7. getCount();

      //捕蟲罐2
     g_IRRecvD8.IRRecvCount(timemeow);
     long Count4 = g_IRRecvD8. getCount();

     g_IRRecvD9.IRRecvCount(timemeow);
     long Count5 = g_IRRecvD9. getCount();

     g_IRRecvD10.IRRecvCount(timemeow);
     long Count6 = g_IRRecvD10. getCount();

      //捕蟲罐3
     g_IRRecvD11.IRRecvCount(timemeow);
     long Count7 = g_IRRecvD11. getCount();

     g_IRRecvD12.IRRecvCount(timemeow);
     long Count8 = g_IRRecvD12. getCount();

     g_IRRecvD13.IRRecvCount(timemeow);
     long Count9 = g_IRRecvD13. getCount();


     //UV
     float UVsensorVoltage; 
     float UVsensorValue;
 
     UVsensorValue = analogRead(A2);
     UVsensorVoltage = UVsensorValue/1024*3.3;
     
 //wind
     windsensorValue = analogRead(windPin);
   // if (windsensorValue == 0 || windsensorValue == 1023) return;
     windsensorVoltage = windsensorValue * .004882814;
   //int nMapSensorVal = map(sensorValue, 0, 1023, 0.4, 2);
    if (windsensorVoltage <= 0.4)
       windSpeed = 0;
     else
     {
      windSpeed = (windsensorVoltage-0.4) * 10 * 2;
     }

     
    //rain
    RR=digitalRead(rainpin);
    //delay(500);
   

/////////////////////////////////////////////////////////// 
     //LED開關
     //digitalWrite(3,LED_S);
    //蟲罐    
    Serial.println("--------Can_1---------"); 
    Serial.println(Count1);
    Serial.println(Count2);
    Serial.println(Count3);
   Serial.println("--------Can_2---------"); 
    Serial.println(Count4);
    Serial.println(Count5);
    Serial.println(Count6);
    Serial.println("--------Can_3---------"); 
    Serial.println(Count7);
    Serial.println(Count8);
    Serial.println(Count9);
  //Serial.println("--------Can_4---------"); 
  //Serial.println(Count10);
  //Serial.println(Count11);
   Serial.println("-----------------------------------------");
    //LED開關
    Serial.println("--------LED---------"); 
    Serial.println(LED_S);
    Serial.println("-----------------------------------------");
    //UV
    Serial.print("UVsensor reading = ");
    Serial.print(UVsensorValue);
    Serial.println("");
    Serial.print("UVsensor voltage = ");
    Serial.print(UVsensorVoltage);
    Serial.println(" V");
   // delay(1000);
    Serial.println("-----------------------------------------");
 //////大氣壓
   float pressure;
   Serial.print("Temp: ");
   Serial.print(bme280.getTemperature());
   Serial.println("C");
   Serial.print("Pressure: ");
   Serial.print(pressure = bme280.getPressure());
   Serial.println("Pa");
   Serial.print("Altitude: ");
   Serial.print(bme280.calcAltitude(pressure));
   Serial.println("m");
   Serial.print("Humidity: ");
   Serial.print(bme280.getHumidity());
   Serial.println("%"); 
   //delay(1000);
   Serial.println("-----------------------------------------");
    //土壤濕度FDS100
    float mudV = analogRead( mudhumpin );
    float mudhum = (mudV/3.3*100);
    if( mudhum>0)
    {
     Serial.print("MudSensor Output:");
     Serial.println(mudhum); 
    // Serial.println(" %");
    }
   else
   {
    Serial.println("Sensor Error");   
   }
    //delay(200);   
  Serial.println("-----------------------------------------");

//wind
  Serial.print("WindSensor Value: ");
  Serial.print(windsensorValue);
  Serial.print("\t");
  Serial.print("WindSensor Voltage: ");
  Serial.print(windsensorVoltage);
  Serial.println("\t");
  //Serial.print("Wind Speed: ");
  //Serial.println(windSpeed);
  //delay(100); 

  //rain
  Serial.println("-----------------------------------------");
  Serial.print("RainState:");
  Serial.println(RR);
  Serial.println("Rainmeter");
  Serial.print(rainmeter);
  Serial.println("mm");

  Serial.println("-----------------------------------------");
}
