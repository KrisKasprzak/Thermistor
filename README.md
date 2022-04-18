# Thermistor
<b><h2><center>Updates </center>
<li>4/18/2021, initial creation</li>
</h1></b>
<br>
<b><h2><center>Thermistors</center></h1></b>

This library is intended to be used with thermistors of type NTC or PTC. This library will convert the thermistors resistance to a temperature given the thermistors B-value, center temperature and center resistence (the typical approach), or if you have the thermistors thermal constants (less popular method). Methods are provided for you to measure the resistence, pass that resistence in, and get a temperature back, or you can pass in an analog pin, number of averages, and a few other parameters and the library will get the average and send back the temperature. Note this "autoMeasure" approach is blocking and will not return control until the measurements are made.

<b>Create the object based on how you want to compute the tempeature</b>

<ul>
	<li>If you have the B-value, center temp and center resistance</li>
	Thermistor(double B, double CenterTempC, double CenterResistance);
</ul>
<ul>
  	<li>if you have 3 thermal constances as reported by the data sheet</li>
	Thermistor(double R1, double ConstA1, double ConstB1, double ConstC1);
</ul>
<ul>
  	<li>if you have 4 thermal constances as reported by the data sheet</li>
	Thermistor(double R1, double ConstA1, double ConstB1, double ConstC1, double ConstD1);
</ul>
  
  
  Use the begin method to designate how you want computations made
 <ul>
  	<li>If your code measures, averages, and computes the thermistors resistance, omit arguements in the begin method. Then use the getTempX, passing in the 	resistence and a temp is returned</li>
	<br>
	void begin();
	<br>
	double getTempF(double Resistance = 0.0);
 </ul>
  <ul>
  	<li>If you want the library to measure, average, and compute temperatures pass in the analog pin, and other parameters to the begin method. Then use the 	getTempX and omit any arguements</li>
	<br>
  	void begin(int AnalogReadPin, unsigned long ReadSamples, unsigned long ReadResolution, unsigned long R1, double VoltageDividerVolts);
	<br>
	double getTempF();
	 </ul>

<b>Typical Wiring</b>
	<br>
	![header image](https://raw.github.com/KrisKasprzak/Thermistor/Images/master/Wiring.jpg)
  <br>
<b>Typical Wiring</b>
 1. Use a voltage divider as shown above
 2. measure the bits at the analog pin
 3. convert bits to volts
 4. using a voltage divider equation Vo = Vi (R2 / (R1 + R2))
 5. Use the equation to solve for R2 (R2 (Vi * R1) / (Vo - Vi);
 6. Pass R2 in to the getTempF, getTempC, getTempK, or getTempR methods


<b>Tips on reducing noisy readings</b>
1. add decoupling capacitors to the power supply for the voltage divider (100 uF and 0.1 uF to start)
2. add decoupling capactitors across the thermistor (10 uF and 0.1 uF to start)
3. use averaging
4. user AGND if you are using a Teensy AGND is a more insulated ground intended for analog pins
5. use 10 bit resolution input if you are using a Teensy 4.0, Teensy 3.2 seem clean at even 12 bits (analogReadRes(BIT))
6.

