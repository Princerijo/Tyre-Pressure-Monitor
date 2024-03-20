#include <RH_ASK.h> //radio head library (it provides complete object oriented library for sending and receiving signals
#include <SPI.h> //serial peripheral interface (synchronous serial data protocol which used to communicate one or more devices over short distance)
#include <Wire.h> // i2c protocol (2wire interface)
#include <SFE_BMP180.h> //

SFE_BMP180 bmp180;

int Altitude = 533; //reference number to BMP 180 about the sea level altitude 
 

RH_ASK rf_driver; // Create Amplitude Shift Keying Object
String output;
 
void setup() 
{
  Serial.begin(9600); //serial monitor to check the arduino
  bool success = bmp180.begin(); // to check the sensor is working or not
  
  rf_driver.init(); // Initialize ASK Object
  if (success) 
  {
    Serial.println("BMP180 init success");
  }
  
 
}
 
void loop()  //read the sensor input make some conversions then encode the data and transmit
{
  char status;
  double T, P;
  bool success = false;

  status = bmp180.startTemperature();

  if (status != 0) {
    delay(1000);
    status = bmp180.getTemperature(T);

    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);

        if (status != 0) {
          float comp = bmp180.sealevel(P, Altitude);
          float a = (comp* 0.0145037738);

          output = String(a);
          static char *msg = output.c_str();
    
          rf_driver.send((uint8_t *)msg, strlen(msg));
          rf_driver.waitPacketSent();
          
          Serial.print("Pressure: ");
          Serial.print(a);
          Serial.println(" psi");
        }
      }
    }
  }
    
  
}