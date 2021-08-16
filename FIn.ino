//Senssor Humedad Temperatura
// Data - Pin 7 Digital
// VCC - 3.3V
//GND - GND 
#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

//LCD NOKIA
#include <LCD5110_Graph.h>
LCD5110 myGLCD(8,9,10,11,12);
extern unsigned char TinyFont[];
extern unsigned char SmallFont[];
extern unsigned char MediumNumbers[];

//Modulo Reloj
//SCL - PIN 17
//SDA - PIN 16
//GND - GND
//VCC - 3.3V
#include <Wire.h> 
#include "RTClib.h"
#include <LiquidCrystal.h>

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
RTC_DS1307 RTC;
int f;

void setup() {
  pinMode(6, OUTPUT);
  //Senssor Humedad Temperatura
  Serial.begin(9600);
  dht.begin();

  //Modulo Reloj
  Wire.begin(); // Inicia el puerto I2C
  RTC.begin(); // Inicia la comunicación con el RTC
  RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
  //Serial.begin(9600); // Establece la velocidad de datos del puerto serie
  //lcd.begin(20,4);

  // LCD NOKIA
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  myGLCD.print("ARDUINO", CENTER, 0);
  myGLCD.print("WATCH", CENTER, 10);
  myGLCD.print("SPORT", CENTER, 20);
  myGLCD.drawRect(26, 8, 58,18);
  for (int i=0; i<6; i++)
  {
    myGLCD.drawLine(58, 8+(i*2), 83-(i*3), 8+(i*2));
    myGLCD.drawLine((i*3), 18-(i*2), 26, 18-(i*2));
  }
  
  myGLCD.setFont(TinyFont);
  myGLCD.print("(C)2015 by", CENTER, 36);
  myGLCD.print("Alexis Lozada", CENTER, 42);
  myGLCD.update();
  //delay(2000);
  
 for (int p=5; p>0; p--)
 {
    myGLCD.setFont(SmallFont);
    myGLCD.drawRect(73,37, 82,47);
    myGLCD.printNumI(p,75,39, 1);
    myGLCD.update();
    delay(1000);
  }
  myGLCD.clrScr();

}

void loop() {
    char resultButton[7] = "null";
    //Senssor Humedad Temperatura
    int h = dht.readHumidity();// Lee la humedad
    int t= dht.readTemperature();//Lee la temperatura
    myGLCD.setFont(TinyFont);
    myGLCD.print("TEMPERATURE HUMEDITY", CENTER, 32);
    myGLCD.setFont(SmallFont);

    //HUMEDAD
    myGLCD.printNumI(h,57,39);
    myGLCD.print("%",69,39);
    // myGLCD.drawRect(48,30,83,40);
  
    //TEMPERATURA
    myGLCD.printNumI(t,13,39 , 1); //Imprimir Variable
    myGLCD.drawLine(47,30,47,47); // Linea Verticañ
    myGLCD.drawRect(0,30, 82,47); // Rectangulo
    myGLCD.drawRect(26,38,28,41); // Grado
    myGLCD.print("C",29,39);      // Centigrados

  //Modulo Reloj
    DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
    myGLCD.drawRect(0,0,82,10); // Rectangulo
    myGLCD.printNumI(now.day(),12,2, 1); //Imprimir Variable
    myGLCD.print("/",25,2);
    myGLCD.printNumI(now.month(),31,2 , 1); //Imprimir Variable
    myGLCD.print("/",44,2);
    myGLCD.printNumI(now.year(),50,2, 1); //Imprimir Variable
    
    myGLCD.setFont(MediumNumbers);
    myGLCD.printNumI(now.hour(),1,13); //Imprimir Variable
    myGLCD.drawRect(26,17,28,19);
    myGLCD.drawRect(26,22,28,24);
    myGLCD.printNumI(now.minute(),30,13); //Imprimir Variable
    myGLCD.drawRect(55,17,57,19);
    myGLCD.drawRect(55,22,57,24);
    myGLCD.printNumI(now.second(),59,13);
    f=now.second();
    Serial.println(f);
    delay(100);
    myGLCD.update();
    myGLCD.clrScr();
    
    
}









