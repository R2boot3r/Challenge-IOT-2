#include <SPI.h>
#include <LoRa.h>


#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C


int counter = 0;
int idlora = 321;


/////////        Initialisation        //////////

void setup() {
  
  bool status;
  
  Serial.begin(9600);
  
  //while (!Serial);

    //Serial.println("LoRa Sender");


   status = bme.begin(0x76); 
    
   if (!status) {
       Serial.println("Could not find a valid BME280 sensor, check wiring!");
       while (1);
   }

  
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);


    
  }
}


//////////// Programme principal ///////////

void loop() {
  int presence=0;

  
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print(idlora);
  LoRa.print(";");
  LoRa.print(getBME('C'));
  LoRa.print(";");
  LoRa.print(getBME('H'));
  LoRa.print(";");
  LoRa.print(presence);
  LoRa.println(";");
  LoRa.endPacket();
  ++counter;
  delay(5000);
}




////////////////////////////////////// Fonctions ////////////////////////////////////////



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
 
