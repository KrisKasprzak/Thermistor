/*

This example shows how to use a thermistor 
1) if the devices data sheet provides the b value (and center temp and resistance)
2) when it's desired to have the library take readings and average them, 
basically do all the analogRead() work

The downside to letting the library read the values is that it's blocking, see the
other examples for non-blocking

*/

#include "Thermistor.h"
#include <elapsedMillis.h>

float tempf;

//from the vishay data sheet
// this object creation is where you pass in
// a) the thermistors B value
// b) the center temperature
// c) the center resistance
Thermistor t(3977, 25.0, 10000.0);

// great library for handling time-based update routines
elapsedMillis Update;

void setup() {

  Serial.begin(115200);
  
  // this begin method is where you pass in
  // a) the analog pin
  // b) the number of averages per readings
  // c) the max bit resolution for the analog read
  // d) R1 value for the voltage divider (R2 is the thermistor for and NTC)
  // e) the MCU's Vcc
  
  t.begin(A1, 5000, 1024.0, 10000.0, 5.0);
  
  // reset the update counter object
  Update = 0;
}

void loop() {
	
  if (Update > 500) {
	// measure the temp every 500 ms
	// all you need to do is getTempF (or getTempC, or getTempK)
	// the fucntion knows you want it to read the analog pin and average the data
    tempf = t.getTempF();
	
    Serial.println(tempf,4);
	// reset the update counter object
	Update = 0;
  }
  
}
