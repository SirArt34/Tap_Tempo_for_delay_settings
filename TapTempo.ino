#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);
#define BACKLIGHT_PIN 3

#include <ArduinoTapTempo.h>

const int BUTTON_PIN = 5;

int whole = 0;
int half = 0;
int quarter = 0;
int eighth = 0;
int sixteenth = 0;
int bpm = 0;

// make an ArduinoTapTempo object
ArduinoTapTempo tapTempo;


void setup() {
  // begin serial so we can see the state of the tempo object through the serial monitor
 Serial.begin(9600);
  lcd.begin (20,4);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);

  // setup your button as required by your project
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);
}

void loop() {
  bpm = tapTempo.getBPM();
  quarter = tapTempo.getBeatLength();
  whole = quarter * 4;
  half = quarter * 2;
  eighth = quarter / 2;
  sixteenth = quarter / 4;
  
  // get the state of the button
  boolean buttonDown = digitalRead(BUTTON_PIN) == LOW;
  
  // update ArduinoTapTempo
  tapTempo.update(buttonDown);

 // Serial.print("bpm: ");
 // Serial.println(tapTempo.getBPM());

  // uncomment the block below to demo many of ArduinoTapTempo's methods
  // note that Serial.print() is not a fast operation, and using it decreases the accuracy of the the tap timing
  
  /*
  Serial.print(",\tbpm: ");
  Serial.print(bpm);
    
  Serial.print(" 1: ");
  Serial.print(whole);
  Serial.print("ms ");
  Serial.print("1/2 ");
  Serial.print(half);
  Serial.print("ms ");
  Serial.print("1/4 ");
  Serial.print(quarter);
  Serial.print("ms ");
  Serial.print("1/8 ");
  Serial.print(eighth);
  Serial.print("ms ");
  Serial.print("1/16 ");
  Serial.print(sixteenth);
  Serial.println("ms ");
  */
  lcd.setCursor(17, 0);
  lcd.print(bpm);
  lcd.print("   ");
  lcd.setCursor(0, 0);
  lcd.print("1:  ");
  lcd.print(whole);
  lcd.print("ms");
  lcd.setCursor(0, 1);
  lcd.print("1/2 ");
  lcd.print(half);
  lcd.print("ms ");
  lcd.setCursor(0, 2);
  lcd.print("1/4 ");
  lcd.print(quarter);
  lcd.print("ms ");
  lcd.setCursor(0, 3);
  lcd.print("1/8 ");
  lcd.print(eighth);
  lcd.print("ms ");
  lcd.setCursor(10, 3);
  lcd.print("1/16 ");
  lcd.print(sixteenth);
  lcd.print("ms ");
  
}
