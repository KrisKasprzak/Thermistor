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


#ifndef THERMISTOR_h
#define THERMISTOR_h

#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define COMPUTE_B_METHOD  0
#define COMPUTE_C3_METHOD 1
#define COMPUTE_C4_METHOD 2



class Thermistor {

	public:

	Thermistor(double B, double CenterTempC, double CenterResistance);
	Thermistor(double R1, double ConstA1, double ConstB1, double ConstC1);
	Thermistor(double R1, double ConstA1, double ConstB1, double ConstC1, double ConstD1);
	void begin();
	void begin(int AnalogReadPin, unsigned long ReadSamples, unsigned long ReadResolution, unsigned long R1, double VoltageDividerVolts);

	double getTempF(double Resistance = 0.0);
	double getTempC(double Resistance = 0.0);
	double getTempK(double Resistance = 0.0);
	double getTempR(double Resistance = 0.0);

	private:
	
	void ComputeTemps();
	byte method;
	int pin;
	double a1, b1, c1, d1, tempk, r1, r2, ct, cr;
	double arr, vdv, volts, bVal;
	unsigned long i, samples, bits;

};

#endif 
