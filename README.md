# Thermistor
<b><h2><center>Updates </center>
<li>4/18/2021, initial creation</li>
</h1></b>
<br>
<b><h2><center>Thermistors</center></h1></b>

This library is intended to be used with thermistors of type NTC or PTC. This library will convert the thermistors resistance to a temperature given the thermistors B-value, center temperature and center resistence (the typical approach), or if you have the thermistors thermal constants (less popular method). Methods are provided for you to measure the resistence, pass that resistence in, and get a temperature back, or you can pass in an analog pin, number of averages, and a few other parameters and the library will get the average and send back the temperature. Note this "autoMeasure" approach is blocking and will not return control until the measurements are made.

Create the object based on how you want to compute the tempeature

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
	void begin();
	
  	double getTempF(double Resistance = 0.0);
 </ul>
  <ul>
  	<li>If you want the library to measure, average, and compute temperatures pass in the analog pin, and other parameters to the begin method. Then use the 	getTempX and omit any arguements</li>
  	void begin(int AnalogReadPin, unsigned long ReadSamples, unsigned long ReadResolution, unsigned long R1, double VoltageDividerVolts);
	double getTempF();
	 </ul>
	Typical Wiring
	
	![header image](https://raw.github.com/KrisKasprzak/Thermistor/master/Images/Wiring.jpg)
  
  How to compute a resistence
 1. Use a voltage divider
