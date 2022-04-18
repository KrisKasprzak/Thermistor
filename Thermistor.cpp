/*
 
  The MIT License (MIT)
  Copyright (c) 2019 Kris Kasrpzak
  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  
  On a personal note, if you develop an application or product using this library 
  and make millions of dollars, I'm happy for you!

  This library is intended to be used with thermistors where you know either

	a) the b-value center temp and center resistance
	b) a1, b1, c1 constants for the thermistors
	c) a1, b1, c1, d1 constants for the thermistors


  Revision		Data		Author			Description
  1.0			4/18/2022	Kasprzak		Initial creation

  
example data sheet that uses b-value or constants
https://www.vishay.com/thermistors/ntc-rt-calculator/

link to how temp is computed from resistance
https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation


*/

#include "Thermistor.h"

Thermistor::Thermistor(double B, double CenterTempC, double CenterResistance) {

	method = COMPUTE_B_METHOD;

	bVal = B;
	ct = CenterTempC + 273.15f;
	cr = CenterResistance;

}
Thermistor::Thermistor(double R1, double ConstA1, double ConstB1, double ConstC1) {

	r1 = R1;
	a1 = ConstA1;
	b1 = ConstB1;
	c1 = ConstC1;
	d1 = 0;

	method = COMPUTE_C3_METHOD;

}

Thermistor::Thermistor(double R1, double ConstA1, double ConstB1, double ConstC1, double ConstD1) {

	r1 = R1;
	a1 = ConstA1;
	b1 = ConstB1;
	c1 = ConstC1;
	d1 = ConstD1;
	method = COMPUTE_C4_METHOD;

}

void Thermistor::begin() {

	samples = 0;

}

void Thermistor::begin(int AnalogReadPin, unsigned long ReadSamples, unsigned long ReadResolution, unsigned long R1, double VoltageDividerVolts) {

	pin = AnalogReadPin;
	samples = ReadSamples;
	arr = (double) ReadResolution;
	r1 = (double) R1;
	vdv = VoltageDividerVolts;
	
}

void Thermistor::ComputeTemps(){

	if (samples > 0) {
		bits = 0;
		for (i = 0; i < samples; i ++){
			bits = bits + analogRead(pin);
		}
		bits = bits / samples;
		volts = ((double) bits) * vdv / arr;

		// voltage divider calculation
		// vo = 5 * r2 /(r1+r2)
		// solve for r2
		// get the exact value for voltage divider r1
		r2 = ( volts * r1) / (vdv - volts);
	}

	if (method == COMPUTE_B_METHOD) {
		tempk = ct / ( 1.0f - ((log(cr / r2) / bVal) * ct));
	}
	else if (method == COMPUTE_C3_METHOD) {
		tempk = 1.0f / (a1 + (b1 * (log(r2 / 10000.0f))) + (c1 * pow(log(r2 / 10000.0f), 2)));
	}
	else if (method == COMPUTE_C4_METHOD) {
		tempk = 1.0 / (a1 + (b1 * (log(r2 / 10000.0f))) + (c1 * pow(log(r2 / 10000.0f), 2)) + (d1 * pow(log(r2 / 10000.0f), 3)));
	}

}

double Thermistor::getTempF(double Resistance){
	r2 = Resistance;
	ComputeTemps();
	return (tempk * 1.8f) - 459.67f;;

}
double Thermistor::getTempC(double Resistance){
	r2 = Resistance;
	ComputeTemps();
	return tempk - 273.15;

}
double Thermistor::getTempK(double Resistance){
	r2 = Resistance;
	ComputeTemps();
	return tempk;
}
double Thermistor::getTempR(double Resistance){
	r2 = Resistance;
	ComputeTemps();
	return tempk;
}



