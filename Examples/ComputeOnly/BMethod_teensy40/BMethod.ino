/*

This example shows how to use a thermistor 
1) if the devices data sheet provides the b value (and center temp and resistance)
2) when it's desired do your own analogRead() work to prevent blocking

*/

#include "Thermistor.h"
#include <elapsedMillis.h>

float volts, r2, temp1f;
unsigned long bits, count, Point;

//from the vishay data sheet
// this object creation is where you pass in
// a) the thermistors B value
// b) the center temperature
// c) the center resistance
Thermistor t(3977.0, 25.0, 10000.0);

// great library for handling time-based update routines
elapsedMillis Update;

void setup() {

  Serial.begin(57600);
  
  // crank up the resolution
  // but connect the thermistor ground to AGnd for lower noise
  analogReadRes(12);
  // this begin method with no arguements tells the library
  // you will do your own analog read
  t.begin();

  // reset the update counter
  Update = 0;

}

void loop() {
	
  // measure the analog pin until update is triggered
  // non blocking method
	
  bits = bits + analogRead(A1);
  count++;

  if (Update > 1000) {

	// average
	// and compute R2 using standard voltage divider math
    bits = bits / count;
	// Teensy Vcc is 3v3 and since we are using 12 bit resolution
	// need a different constant (4096)
    volts = (float) bits * 3.3f / 4096.0f;
    r2 = ( volts * 10000.0f) / (3.3f - volts);
	// because you specified in begin you will do your own analog read
	// you need to pass in R2  to getTempF (or getTempC, or getTempK)
    temp1f = t.getTempF(r2);

	//  not needed but show the current data point
	Point++;

	// print it all out
    Serial.print("Read: ");         Serial.print(Point);       Serial.print(", ");
    Serial.print("Averages: ");     Serial.print(Averages, 0); Serial.print(", ");
    Serial.print("Temp [deg F]: "); Serial.println(temp1f, 2);

    // reset counter and bits and update object
    bits = 0.0f;
    count = 0.0f;
    Update = 0;
	
  }
}

