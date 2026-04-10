#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

#define SDA A4
#define SCL A5

#define sensPin A0
#define Rpin 11
#define Gpin 10
#define Bpin 9

struct color 
{
public:
  int r;
  int g;
  int b;
};

color sampleColors[4]; //red, green, blue, yellow
LiquidCrystal_I2C lcd(0x27, 16, 2);

void clearRGB(){
  analogWrite(Rpin,0);
  analogWrite(Gpin,0);
  analogWrite(Bpin,0);
}

void learnColors(color* sampleColors){
  const int numOfSamples = 1000;
  const int waitTime = 4000;

  for (int i=0; i<4; i++){
    lcd.setCursor(0, 0);
    lcd.clear(); 
    lcd.print("Place colour "); lcd.print(i+1);
    delay(waitTime);

    color sampleColor;
    for (int k=0; k<3; k++){
      clearRGB();
      delay(100);
      switch (k) {
        case 0: analogWrite(Rpin, 255); break;
        case 1: analogWrite(Gpin, 255); break;
        case 2: analogWrite(Bpin, 255); break;
      }
      delay(200);
      
      long int sum = 0;
      lcd.clear(); 
      lcd.setCursor(0, 0);
      lcd.print("Odczyt...");
      for(int j=0; j<numOfSamples; j++){
        sum = sum + analogRead(sensPin);
        delay(2);
      }

      switch (k) {
        case 0: sampleColor.r = sum / numOfSamples; break;
        case 1: sampleColor.g = sum / numOfSamples; break;
        case 2: sampleColor.b = sum / numOfSamples; break;
      }
    }
    sampleColors[i] = sampleColor;
    Serial.print("Model: "); Serial.print(i+1);
    Serial.print(": R="); Serial.print(sampleColor.r);
    Serial.print(" G="); Serial.print(sampleColor.g);
    Serial.print(" B="); Serial.println(sampleColor.b);
  }

  clearRGB();
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Calibration DONE");
  delay(waitTime);
  lcd.clear(); 
  lcd.setCursor(0, 0);
}

void readColor(color* sampleColors){
  const int numOfSamples = 1000;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Place colour");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Detection...");

  color readColor;
  for (int k=0; k<3; k++){
      clearRGB();
      delay(100);
      switch (k) {
        case 0: analogWrite(Rpin, 255); break;
        case 1: analogWrite(Gpin, 255); break;
        case 2: analogWrite(Bpin, 255); break;
      }
      delay(200);
      
      long int sum = 0;
      for(int j=0; j<numOfSamples; j++){
        sum = sum + analogRead(sensPin);
        delay(2);
      }

      switch (k) {
        case 0: readColor.r = sum / numOfSamples; break;
        case 1: readColor.g = sum / numOfSamples; break;
        case 2: readColor.b = sum / numOfSamples; break;
      }
    }

    Serial.print("Reading: R="); Serial.print(readColor.r);
    Serial.print(" G="); Serial.print(readColor.g);
    Serial.print(" B="); Serial.println(readColor.b);

    float dist = INFINITY;
    int numOfColor = 0;
    for (int i=0;i<4;i++){
      float distTemp = sqrtf(powf(readColor.r - sampleColors[i].r,2) + 
      powf(readColor.g - sampleColors[i].g,2) + powf(readColor.b - sampleColors[i].b,2)) ;

      if (dist > distTemp){
        dist = distTemp;
        numOfColor = i;
      }
    }

    lcd.clear(); 
    lcd.setCursor(0, 0);
    switch (numOfColor){
      case 0:{
        lcd.print("Red");
        break;
      }
      case 1:{
        lcd.print("Green");
        break;
      }
      case 2:{
        lcd.print("Blue");
        break;
      }
      case 3:{
        lcd.print("Yellow");
        break;
      }
      default:{
        lcd.print("Reading error");
        break;
      }
    }
    delay(3000);

}

void setup() {
  Serial.begin(9600);
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  
  pinMode(sensPin, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  learnColors(sampleColors);
}

void loop() {
  readColor(sampleColors);
}