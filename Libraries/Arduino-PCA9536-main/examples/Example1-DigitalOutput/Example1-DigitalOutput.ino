/*
  Using the PCA9536 -- Digital Output
  By: Jim Lindblom
  SparkFun Electronics
  Date: May 4, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14733
  This example demonstrates how to use pinMode and digitalWrite/write to set output values of the PCA9536
  
  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the Qwiic RGB Sensor onto the shield
  Watch each LED turn on one-at-a-time
*/

#include <PCA9536D.h>

PCA9536 io;

void setup()
{
  Serial.begin(115200);
  Serial.println("PCA9536 example");

  Wire.begin();

  // Initialize the PCA9536 with a begin function
  if (io.begin() == false)
  {
    Serial.println("PCA9536 not detected. Please check wiring. Freezing...");
    while (1)
      ;
  }

  for (int i = 0; i < 4; i++)
  {
    // pinMode can be used to set an I/O as OUTPUT or INPUT
    io.pinMode(i, OUTPUT);
  }
}

void loop()
{
  for (int i = 3; i >= 0; i--)
  {
    // digitalWrite or write can be used to set an I/O value
    // (both perform the same function)
    io.digitalWrite((i + 1) % 4, HIGH); // Turn last pin HIGH
    io.write(i, LOW);                   // Turn this pin LOW
    delay(1000);
  }
}
