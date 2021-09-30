// Includes.
#include "Sodaq_LSM303AGR.h"

#define DEV_I2C Wire    //Or Wire
#define SerialPort Serial

#define CONVERT_G_TO_MS2    9.80665f
#define FREQUENCY_HZ        100
#define INTERVAL_MS         (1000 / (FREQUENCY_HZ + 1))


static unsigned long last_interval_ms = 0;
Sodaq_LSM303AGR accel;

void setup() 
{
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);
    
    SerialPort.begin(57600);
    delay(1000);

    SerialPort.println("BEGIN");
    Wire.begin();
    delay(1000);
   
    if (accel.checkWhoAmI()) {
        SerialPort.println("FOUND ACCEL!");
    }
    else {
        SerialPort.println("NO ACCEL!");
    }
    
    accel.rebootMagnetometer();
    accel.rebootAccelerometer();
    delay(1000);

    accel.enableMagnetometer(Sodaq_LSM303AGR::MagHighResMode, Sodaq_LSM303AGR::Hz100, Sodaq_LSM303AGR::Continuous);
    accel.enableAccelerometer( Sodaq_LSM303AGR::NormalMode, Sodaq_LSM303AGR::HrNormalLowPower25Hz,Sodaq_LSM303AGR::XYZ, Sodaq_LSM303AGR::Scale2g,  true);
    digitalWrite(BUILTIN_LED, LOW);
}

void loop() {
  digitalWrite(BUILTIN_LED, HIGH);


    if (millis() > last_interval_ms + INTERVAL_MS) {
        last_interval_ms = millis();


        Serial.print(accel.getX() * CONVERT_G_TO_MS2);
        Serial.print('\t');
        Serial.print(accel.getY() * CONVERT_G_TO_MS2);
        Serial.print('\t');
        Serial.println(accel.getZ() * CONVERT_G_TO_MS2);
    }


// Output data.
//  SerialPort.print("| Acc[mg]: ");
//  SerialPort.print(accel.getX());
//  SerialPort.print(" ");
//  SerialPort.print(accel.getY());
//  SerialPort.print(" ");
//  SerialPort.print(accel.getZ());
////  
//  SerialPort.print(" | Mag[mGauss]: ");
//  SerialPort.print(accel.getMagX());
//  SerialPort.print(" ");
//  SerialPort.print(accel.getMagY());
//  SerialPort.print(" ");
//  SerialPort.print(accel.getMagZ());
////  SerialPort.print(" | Temp[C]: ");
////  SerialPort.print(temperature, 2);
//  SerialPort.println(" |");
digitalWrite(BUILTIN_LED, LOW);
}
