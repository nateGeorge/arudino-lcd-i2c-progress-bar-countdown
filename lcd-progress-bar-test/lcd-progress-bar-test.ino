// original from http://www.electronics-lab.com/arduino-lcd-horizontal-progress-bar-using-custom-characters/
// Arduino LCD horizontal progress bar using custom characters
// counts down to a targetTime
// tested on a 1602 16x2 HD44780 Character LCD /w IIC/I2C FC-113 Serial Interface Adapter Module

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// uses the New LiquidCrystal library https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home

#define lenght 16.0

double percent=100.0;
unsigned char b;
unsigned int peace;

// custom charaters for the progress bar
// each one is a vertical line

byte p1[8] = {
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10};

byte p2[8] = {
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18};

byte p3[8] = {
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C};

byte p4[8] = {
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E};

byte p5[8] = {
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F};

float targetTime = 30.0; // in seconds
float startTime; // in milliseconds

LiquidCrystal_I2C	lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified module

void setup()   {
  Serial.begin(9600);
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH); // NOTE: You can turn the backlight off by setting it to LOW instead of HIGH
  
  lcd.createChar(0, p1);
  lcd.createChar(1, p2);
  lcd.createChar(2, p3);
  lcd.createChar(3, p4);
  lcd.createChar(4, p5);
  
  lcd.begin(16, 2);
  lcd.clear();
  startTime = millis();
}

void loop()
{
  lcd.setCursor(0, 0);
  
  if (((millis()-startTime)/1000) < targetTime) {

  // calculate time until reached target

  percent = (millis() - startTime)/(1000*targetTime)*100.0;

  lcd.print("startin up...");
  Serial.println(int(targetTime - (millis()-startTime)/1000));
  lcd.print(int(targetTime - (millis()-startTime)/1000));
  lcd.print("s");
  
  lcd.setCursor(0,1);

  double a=lenght/100*percent;

 // drawing black rectangles on LCD

  if (a>=1) {

    for (int i=1;i<=a;i++) {

      lcd.write(byte(4));

      b=i;
    }

    a=a-b;

  }

  peace=a*5;

// drawing charater's colums

  switch (peace) {

  case 0:

    break;

  case 1:
    lcd.write(byte(0));

    break;

  case 2:
    lcd.write(byte(1));
    break;

  case 3:
    lcd.write(byte(2));
    break;

  case 4:
    lcd.write(byte(3));
    break;

  }

//clearing line
  for (int i =0;i<(lenght-b);i++) {

    lcd.print(" ");
  }

  ;
  }
  else{
    lcd.print("you have arrived");
  }
}
