 /***************************************************************************
* BME280 code with 2 extra function to display temperature
* easily
* written and Updated by Ahmad Shamshiri on July 25, 2019 at 18:42 
* in Ajax, Ontario, Canada for Robojax.com
* Watch Video instruction for this code:https://youtu.be/7dwWYn9_OhA
* 
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C



void setup() {
    Serial.begin(9600);
    Serial.println("BME280 test");
    Serial.println(F("BME280 test"));

    bool status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Robojax Test --");
    delay(2000);

    Serial.println();
}


void loop() { 
    // Robojax.com BME280 Code
    Serial.print("Temperature = ");
    Serial.print(getBME('C'));
    printDegree();
    Serial.print("C ");
    Serial.print(getBME('F'));
    printDegree();
    Serial.print("F "); 
    Serial.print(getBME('K'));
    Serial.println("K ");       


    Serial.print("Pressure = ");
    Serial.print(getBME('P'));
    Serial.println(" hPa ");

    Serial.print("Humidity = ");
    Serial.print(getBME('H'));
    Serial.println("% ");
    
    Serial.print("Approx. Altitude = ");
    Serial.print(getBME('A'));
    Serial.println(" m");



    Serial.println();

    // action
    if(getBME('C') <65.2)
    {
     //digitalWrite(5, HIGH); 
    }
    delay(2000);
     // Robojax.com BME280 Code
}// loop end



/*
 * @brief returns temperature or relative humidity
 * @param "type" is character
 *     C = Celsius
 *     K = Keliven
 *     F = Fahrenheit
 *     H = Humidity
 *     P = Pressure
 *     A = Altitude
 * @return returns one of the values above
 * Usage: to get Fahrenheit type: getHTU('F')
 * to print it on serial monitor Serial.println(getBME('F'));
 * Written by Ahmad Shamshiri on July 13, 2019. Update july 25, 2019
 * in Ajax, Ontario, Canada
 * www.Robojax.com 
 */
float getBME(char type)
{
   // Robojax.com BME280 Code
  float value;
    float temp = bme.readTemperature();// read temperature
    float pressure = bme.readPressure() / 100.0F; // read pressure
    float rel_hum = bme.readHumidity();// read humidity
    float alt =bme.readAltitude(SEALEVELPRESSURE_HPA);// read altitude
   if(type =='F')
   {
    value = temp *9/5 + 32;//convert to Fahrenheit 
   }else if(type =='K')
   {
    value = temp + 273.15;//convert to Kelvin
   }else if(type =='H')
   {
    value = rel_hum;//return relative humidity
   }else if(type =='P')
   {
    value = pressure;//return pressure
   }else if(type =='A')
   {
    value = alt;//return approximate altitude
   }else{
    value = temp;// return Celsius
   }
   return value;
    // Robojax.com BME280 Code
}//getBME


/*
 * @brief prints degree symbol on serial monitor
 * @param none
 * @return returns nothing
 * Written by Ahmad Shamshiri on July 13, 2019
 * for Robojax Tutorial Robojax.com
 */
 void printDegree()
{
   // Robojax.com Code
    Serial.print("\xC2"); 
    Serial.print("\xB0");  
} 
 
