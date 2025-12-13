
#include <FastLED.h>

using namespace fl;

#define DATA_PIN    13
#define BTN_PIN     4
#define DEMO_BTN_PIN 7

#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    90
CRGB leds[NUM_LEDS];
unsigned long starttime = 0; // Variable to store the time the button was pressed
int startdemo = 0;
bool demoisrunning = false;
bool firstrun = true;

#define BRIGHTNESS          255
int laststate = HIGH; // low == button is being pressed
int btnstate;
int demobuttonstate;
int demobuttonlaststate = HIGH;
void setup() {
  // put your setup code here, to run once:
//delay(3000); // 3 second delay for recovery
Serial.begin(57600);

FastLED.clear();  // clear all pixel data
FastLED.show();

FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed

pinMode(BTN_PIN, INPUT_PULLUP);
pinMode(DEMO_BTN_PIN, INPUT_PULLUP);
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  // startup blink test to confirm LEDs are working.
  
  fill_solid(leds, NUM_LEDS, CRGB(255,0,0));  // fill red
  FastLED.show();
  delay(300);
  fill_solid(leds, NUM_LEDS, CRGB(0,255,0));  // fill green
  FastLED.show();
  delay(300);
  fill_solid(leds, NUM_LEDS, CRGB(0,0,255));  // fill blue
  FastLED.show();
  delay(300);
  turnoff();
  

  //fill_solid(leds, NUM_LEDS, CRGB(0,0,255));  // fill blue
  //FastLED.show();
  //delay(1000);
  //turnoff();
  //turnonwhite();
}

void loop()
 {
  // put your main code here, to run repeatedly:
  
    btnstate = digitalRead(BTN_PIN);
    demobuttonstate = digitalRead(DEMO_BTN_PIN);

if(demoisrunning)
{
  if((demobuttonlaststate == HIGH) && (demobuttonstate == LOW))
  {
  turnoff();
    demoisrunning=false;
}

}
if(
  (demobuttonlaststate == LOW && demobuttonstate == HIGH)
  ||
  (demoisrunning && laststate == HIGH && btnstate == HIGH)
  )
    {
      party();
    }
    // low == button is being pressed
    if (laststate == LOW && btnstate == HIGH)
    {
turnoff();

turnonwhite();
    }

    

     if (demoisrunning && btnstate == HIGH)
    {
      // if (millis() - starttime >= 5000 && !demoisrunning) 
       //{
        //demoisrunnning = true;
        //turnonred();
        //turnongreen();
        //starttime = millis();
       //}
    }
    else
    {
      //if (millis() - starttime >= 5000) demoisrunning = true;
    }
   // if (firstrun) firstrun = false;
//if (laststate == HIGH) turnonred();
//if (laststate == LOW) turnongreen(); // low == button is being pressed
//delay(2000);
    laststate = btnstate;
    demobuttonlaststate = demobuttonstate;
  //  turnoff();
}

void turnonwhite()
{
  demoisrunning = false;
  /*
      for (int i = 0; i < NUM_LEDS; i++) 
      {
          leds[i] = CRGB::White;
        }
        */
        fill_solid(leds, NUM_LEDS, CRGB(255,255,255)); 
  //leds[0] = CRGB::White;
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  delay(5500);
  //turnonred();
  //turnongreen();
  turnoff();
//startdemo = 1;
//starttime = millis();  // Record the time button was pressed
}

void turnonred()
{
  fill_solid(leds, NUM_LEDS, CRGB(0,255,0));
  FastLED.show();
  delay(1000);
}

void turnongreen()
{
  fill_solid(leds, NUM_LEDS, CRGB(255,255,0));
  FastLED.show();
  delay(1000);
}

void turnoff()
{
  /*
      for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB::Black;
        }
        */
        fill_solid(leds, NUM_LEDS, CRGB(0,0,0)); 
  FastLED.show();
 
}

void party()
{
static uint8_t hue = 0;
	demoisrunning = true;
	// First slide the led in one direction
	for(int i = 0; i < NUM_LEDS; i++) {
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(6);
  }
  delay(10);
  	// Now go in the other direction.  
	for(int i = (NUM_LEDS)-1; i >= 0; i--) {
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(6);
	}
delay(10);

}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { 
  //leds[i] = CRGB::Black;
  leds[i].nscale8(25);
   } }
