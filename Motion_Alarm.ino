#include <SD.h>                      // need to include the SD library
#define SD_ChipSelectPin 4           //using digital pin 4 on arduino nano 328
#include <TMRpcm.h>                  //  also need to include this library...
 
TMRpcm tmrpcm;                  // create an object for use in this sketch
int SW1; 
int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int laserpin = 10;              // Laser Light pin
int val = 0;                    // variable for reading the pin status
int pinSpeaker = 9;             // Set up a speaker on a PWM pin (digital 9, 10, or 11)
int pinSpeaker2 = 8;
int siren = 0;
int sirenFreq = 1000;
int pinOne = 5;
int pinTwo = 6;
int pinThree = 7;
int gridCounter = 0;
void setup(){
 pinMode(inputPin, INPUT);      // declare sensor as input
 pinMode(pinSpeaker, OUTPUT);
 pinMode(pinSpeaker2, OUTPUT);
 pinMode(laserpin, OUTPUT);
 pinMode(pinOne, OUTPUT);
 pinMode(pinTwo, OUTPUT);
 pinMode(pinThree, OUTPUT);
 Serial.begin(9600);

 
  tmrpcm.speakerPin = 9;        //11 on Mega, 9 on Uno, Nano, etc
 
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
  return;                       // don't do anything more if not
  }
 digitalWrite(laserpin, LOW);
 tmrpcm.volume(1);
 tmrpcm.play("test.wav");      //the sound file "1" will play each time the arduino powers up, or is reset
}
 
 


void loop(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
   
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      tmrpcm.play("crowd.wav");
      delay(12000);
      tmrpcm.play("animals2.wav");
      delay(5000);
      laserLightOn();
      grid();
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
      delay(150);    
      if (pirState == HIGH){
      // we have just turned off
      Serial.println("Motion ended!");
      laserLightOff();
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
// duration in mSecs, frequency in hertz


void laserLightOn() { 
        digitalWrite(laserpin,HIGH);
        delay(250);
}
void laserLightOff(){
        digitalWrite(laserpin, LOW);
        delay(250);
    }


void grid(){
  while (gridCounter < 80){

    digitalWrite(pinOne,LOW);
    digitalWrite(pinTwo, LOW);
    digitalWrite(pinThree,LOW);
    delay(5);
    digitalWrite(pinOne,HIGH);
    digitalWrite(pinTwo, LOW);
    digitalWrite(pinThree,LOW);
    delay(5);
    digitalWrite(pinOne,LOW);
    digitalWrite(pinTwo, HIGH);
    digitalWrite(pinThree,LOW);
    delay(5);
    digitalWrite(pinOne,HIGH);
    digitalWrite(pinTwo, HIGH);
    digitalWrite(pinThree,LOW);
    delay(5);
    digitalWrite(pinOne,LOW);
    digitalWrite(pinTwo, LOW);
    digitalWrite(pinThree,HIGH);
    delay(5);
    gridCounter++;
}
}

