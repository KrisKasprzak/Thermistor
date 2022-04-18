# Thermistor

<b>Updates</b>
<ul>
<li>4/18/2021 - initial creation (2021 tax day for the USA)</li>
</ul>
<br>

This library is intended to be used with thermistors of type NTC or PTC. This library will convert the thermistors resistance to a temperature given the thermistors B-value, center temperature and center resistance (the typical approach), or if you have the thermistors thermal constants (less popular method). Methods are provided for you to measure the resistance, pass that resistance in, and get a temperature back, or you can pass in an analog pin, number of averages, and a few other parameters and the library will get the average and send back the temperature. Note this "autoMeasure" approach is blocking and will not return control until the measurements are made.
<br>
	![header image](https://raw.github.com/KrisKasprzak/Thermistor/master/Images/Thermistor.jpg)
  <br>
<br>
<b>Create the object based on how you want to compute the temperature</b>

<ul>
	<li>If you have the B-value, center temp and center resistance</li>
	Thermistor MyThermistor(double B, double CenterTempC, double CenterResistance);
</ul>
<ul>
  	<li>if you have 3 thermal constants  as reported by the data sheet</li>
	Thermistor MyThermistor(double R1, double ConstA1, double ConstB1, double ConstC1);
</ul>
<ul>
  	<li>if you have 4 thermal constants  as reported by the data sheet</li>
	Thermistor MyThermistor(double R1, double ConstA1, double ConstB1, double ConstC1, double ConstD1);
</ul>
  
  
  Use the begin method to designate how you want computations made
 <ul>
  	<li>If your code measures, averages, and computes the thermistors resistance, omit arguments in the begin method. Then use the getTempX, passing in the 	resistance and a temp is returned</li>
	<br>
	void begin();
	<br>
	<br>
	double getTempF(double Resistance = 0.0);
 </ul>
  <ul>
  	<li>If you want the library to measure, average, and compute temperatures pass in the analog pin, and other parameters to the begin method. Then use the 	getTempX and omit any arguments </li>
	<br>
  	void begin(int AnalogReadPin, unsigned long ReadSamples, unsigned long ReadResolution, unsigned long R1, double VoltageDividerVolts);
	<br>
	<br>
	double getTempF();
	 </ul>

<b>Typical Wiring</b>
<br>
Thermistors either NTC ot PTC are typically wired in a voltage divider scenario. This allows the voltage to be measured across them and resistance computed. 
<br>
	![header image](https://raw.github.com/KrisKasprzak/Thermistor/master/Images/Wiring.jpg)
<br>
<b>Computing Thermistor Resistance</b>
 1. Use a voltage divider as shown above
 2. Measure the bits at the analog pin
 3. Convert bits to volts using the appropriate bit resolution 1024 for 10 bit MCU's. volts = bits / resolution;
 4. Using a voltage divider equation Vo = Vi (R2 / (R1 + R2))
 5. Use the equation to solve for R2 (R2 (Vi * R1) / (Vo - Vi);
 6. Pass R2 in to the getTempF, getTempC, getTempK, or getTempR methods
 7. Make sure calculations are based on floats or doubles.


<b>Tips on reducing noisy readings</b>
1. Add decoupling capacitors to the power supply for the voltage divider (100 uF and 0.1 uF to start)
2. Add decoupling capactitors across the thermistor (10 uF and 0.1 uF to start)
3. Use averaging
4. Use AGND if you are using a Teensy AGND is a more insulated ground intended for analog pins
5. Use 10 bit resolution input if you are using a Teensy 4.0, Teensy 3.2 seem clean at even 12 bits (analogReadRes(BIT))


<b>Typical reading response chart</b>
<br>
<br>
	![header image](https://raw.github.com/KrisKasprzak/Thermistor/master/Images/Readings.jpg)
<br>
 <br> 
1. Readings for a 30-minute period
2. R1 = 10K resistor
3. Teensy 4.0, 10 bit read resolution
4. 0.1 uF decopuling cap across Thermistor
5. approx 57,000 read per second
6. Recordings taken every 500 ms
7. Test environment: desk in my home office
8. Breadboard mounting, 3 inch jumper wires




