#include "BluetoothSerial.h"
#include <analogWrite.h>
#define redPin 12    
#define greenPin 13  
#define bluePin 14   
#define comPin 27

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
int receivedValue = 0;
// count the red, green and blue and repeat
int rgbLoop = 0;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_kachun"); //Bluetooth device name
  // pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);   
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT);  
  pinMode(comPin, OUTPUT);
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());        
  }
  if (SerialBT.available()) {
    receivedValue = SerialBT.read();    
    if (rgbLoop == 3) {
      // reset
      rgbLoop = 0;
    }
    Serial.print("rgbLoop: " + String(rgbLoop) + "; ");
    Serial.print("Received: " + String(receivedValue) + "; "); 
    analogWrite(comPin, 255);   
    switch(rgbLoop) {
      case 0: // red
        Serial.println("RED: " + String(receivedValue));
        analogWrite(redPin, (255-receivedValue)); 
        break;
      case 1: // green
        Serial.println("GREEN: " + String(receivedValue));
        analogWrite(greenPin, (255-receivedValue));
        break;
      case 2: // blue
        Serial.println("BLUE: " + String(receivedValue));
        analogWrite(bluePin, (255-receivedValue));
        break;
      default:
        Serial.println("Impossible!!!");
    } 
    rgbLoop++;    
  }
  delay(20);
}
