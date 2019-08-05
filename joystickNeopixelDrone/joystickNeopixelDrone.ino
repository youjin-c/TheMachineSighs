#include <Keyboard.h>
#include <Servo.h>
#include <FastLED.h>
#define NUM_LEDS 16
#define DATA_PIN 3
//PWM pinout: 3,5,6,9,10,11,13

CRGB leds[NUM_LEDS];
Servo srv0, srv1, srv2, srv3, esc; 
boolean rtFlag=false;
int srvPos,push,upDown,numLedsToLight, escval;


void setup() {
  pinMode(9, INPUT_PULLUP);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  esc.attach(10); //Specify the esc signal pin,Here as D8
  esc.writeMicroseconds(1000); //initialize the signal to 1000

  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  push = digitalRead(9);
  upDown = analogRead(A0);
  numLedsToLight = map(upDown, 570, 1023, 0, NUM_LEDS);
  escval= map(upDown, 570, 1023,1050,1200);

  ledControl(); 
  joystickControl();
  esc.writeMicroseconds(escval); //using val as the signal to esc
  
  delay(250);

  //Serial.print(buttonValue);
  //Serial.print(',');
  //Serial.print(potValue);
//  Serial.print(',');
//  Serial.print(lightValue);
  Serial.println(escval);
}
void joystickControl(){
  if(push ==HIGH){
    if(rtFlag){
      Keyboard.write('t');
      rtFlag = false;
    }else if(!rtFlag){
      Keyboard.write(0xB0);//return
      rtFlag = true;
    }
  }
  if(upDown >=900){
    Keyboard.write('k');
    rtFlag = true;
  }else if(upDown <=600){
    Keyboard.write('j');
    rtFlag = true;
  }
}
void ledControl(){
  FastLED.clear();
  for(int led = 0; led < numLedsToLight; led++) { 
      leds[led] = CRGB::White; 
  }
  FastLED.show();  
}
