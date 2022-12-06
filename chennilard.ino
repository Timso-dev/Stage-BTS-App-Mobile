// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
int i = 0;
int y = 0;
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        2 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 120 // Popular NeoPixel ring size
int ledPin = 3; 
int valeur = 0;
int x = 250;
// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial mavoieserie(0, 1); // (RX, TX) (pin Rx BT, pin Tx BT)

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  // Ouvre la voie série avec l'ordinateur
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pinMode(ledPin, OUTPUT); 
}

void loop() {
    digitalWrite(ledPin, HIGH);
    valeur = Serial.read();
    Serial.println(valeur, DEC); 
    if (valeur>0){
      x = valeur*10;      
    }
  while(valeur<0){
    digitalWrite(ledPin, HIGH);
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.setPixelColor(y, pixels.Color(0, 0, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
    y=i-2;
    i=i+1;
    valeur = Serial.read();
    Serial.println(valeur, DEC); 
    delay(x); // Pause before next pass through loop
    valeur = Serial.read();
    Serial.println(valeur, DEC); 
    if (i>122){
      i=0;
      pixels.clear(); // Set all pixel colors to 'off'
    }
  }    
}
