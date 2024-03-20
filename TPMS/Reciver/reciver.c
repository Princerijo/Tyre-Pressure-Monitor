#include <RH_ASK.h> // Include dependant SPI Library 
#include <SPI.h> 

#include <LiquidCrystal.h> // initialize the library by associating any needed LCD interface pin



const int rs = 12, en = 10 ,d4 = 5, d5 = 4, d6 = 3, d7 = 2; // with the arduino pin number it is connected to
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


String conversion; // Define output strings
 

String str_out; //String str_temp;
 

RH_ASK rf_driver; // Create Amplitude Shift Keying Object
String a; 

void setup()
{
  pinMode(8, OUTPUT); //Buzzer pin
  
  lcd.begin(16,2); //Tell Arduino to start your 16 column 2 row LCD

  lcd.setCursor(0,0); //Set LCD cursor to upper left corner, column 0, row 0
  lcd.print("Rx Status OK"); //receiver check
  
  lcd.setCursor(0,1); //Set LCD cursor to upper left corner, column 0, row 1
  lcd.print("Waiting for tx"); //transmitter check

        
  rf_driver.init(); // Initialize ASK Object
    
  Serial.begin(9600); // Setup Serial Monitor
}
 
void loop() // get the message from the receiver and decode it then display in LCD
{
    
    uint8_t buf[6]; // Set buffer to size of expected message
    uint8_t buflen = sizeof(buf);
    
    
    if (rf_driver.recv(buf, &buflen)) // Check if received packet is correct size
    {
      
      // Message received with valid checksum
      // Get values from string
      
      // Convert received data into string
      str_out = String((char*)buf);
      
      // Split string into two values
      for (int i = 0; i < str_out.length(); i++) 
      {
      conversion = str_out.substring(i);
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TPMS");
      
      lcd.setCursor(0,1);
      lcd.print("psi=");
      lcd.print(conversion);
      
      a = (conversion);
      

      if (a<="14.85")
      { 
        tone(8, 3000, 500);
        delay(50);
        tone(8, 1000, 500);
        delay(20);
        tone(8, 2000, 500);
        delay(50);
       
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Warning!!!");
        lcd.setCursor(0,1);
        lcd.print("Low Pressure");
      }
      else
      {
      digitalWrite(8, LOW);
      }
      break;
      }
    }
}