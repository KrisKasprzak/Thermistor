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
// a) the thermistors center temperature
// b) a1, b1, c1, d1 contstants as read directly from the devices data sheet

Thermistor t(10000, 3.354016E-03, 2.569850E-04, 2.620131E-06, 6.383091E-08);

// great library for handling time-based update routines
elapsedMillis Update;

void setup() {

  Serial.begin(57600);
  
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
    volts = (float) bits * 5.0f / 1024.0f;
    r2 = ( volts * 10000.0f) / (5.0f - volts);
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

