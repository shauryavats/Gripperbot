#include <AFMotor.h>

//DUALSHOCK3 CONTROLLED GRIPPER BOT
#include <PS3BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

AF_DCMotor motorR(1);
AF_DCMotor motorL(2);
AF_DCMotor motorXaxis(3);
AF_DCMotor motorYaxis(4);

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
//PS3BT PS3(&Btd); // This will just create the instance
PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;

void setup() {
  Serial.begin(9600);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  motorR.setSpeed(255);//right
  motorL.setSpeed(255);//left
  motorXaxis.setSpeed(180);//xaxis
  motorYaxis.setSpeed(255);//yaxis

  delay(5000);
}
void loop() {
  Usb.Task();
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    
    if(PS3.getAnalogHat(LeftHatY) > 90 && PS3.getAnalogHat(LeftHatY) <120){
      Serial.print(F("\r\nLeftHatY:STOP STOP"));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      motorR.run(RELEASE);
      motorL.run(RELEASE);
      motorYaxis.run(RELEASE);
      motorXaxis.run(RELEASE);    
    }
    if(PS3.getAnalogHat(LeftHatX) > 110 && PS3.getAnalogHat(LeftHatX) < 135){
      Serial.print(F("\r\nLeftHatY:STOP STOP"));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      motorR.run(RELEASE);
      motorL.run(RELEASE);
      motorYaxis.run(RELEASE);
      motorXaxis.run(RELEASE);
    }
    //go forward
    if (PS3.getAnalogHat(LeftHatY) == 0) {
      Serial.print(F("\r\nLeftHatY:GO FORWARD "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      motorR.run(BACKWARD);
      motorL.run(FORWARD);
      motorYaxis.run(RELEASE);
      motorXaxis.run(RELEASE);
    }

    //go backward
    if (PS3.getAnalogHat(LeftHatY) == 255) {
      Serial.print(F("\r\nLeftHatY: GO BACKWARD "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      motorL.run(BACKWARD);
      motorR.run(FORWARD);
      motorYaxis.run(RELEASE);
      motorXaxis.run(RELEASE);
    }

    //turn left
    if (PS3.getAnalogHat(RightHatX) == 0) {
      Serial.print(F("\r\RightHatX: TURN LEFT "));
      Serial.print(PS3.getAnalogHat(RightHatX));
      motorL.run(BACKWARD);
      motorR.run(RELEASE);
      motorYaxis.run(RELEASE);
      motorXaxis.run(RELEASE);

    }

    //turn right
    if (PS3.getAnalogHat(RightHatX) == 255) {
      Serial.print(F("\r\RightHatX; TURN RIGHT"));
      Serial.print(PS3.getAnalogHat(RightHatX));
      motorL.run(RELEASE);
      motorR.run(BACKWARD);
      motorYaxis.run(RELEASE);
      motorXaxis.run(RELEASE);
    }

    //grab
    if (PS3.getAnalogButton(L1)) {
      Serial.print(F("\r\nL1: GRAB "));
      Serial.print(PS3.getAnalogButton(L1));
      motorXaxis.run(FORWARD);
      motorL.run(RELEASE);
      motorR.run(RELEASE);
      motorYaxis.run(RELEASE);
    }

    //release
    if (PS3.getAnalogButton(L2)) {
      Serial.print(F("\r\nL2:RELEASE "));
      Serial.print(PS3.getAnalogButton(L2));
      motorXaxis.run(BACKWARD);
      motorL.run(RELEASE);
      motorR.run(RELEASE);
      motorYaxis.run(RELEASE);
    }

    //UP
    if (PS3.getAnalogButton(R1)) {
      Serial.print(F("\r\nR1:UP "));
      Serial.print(PS3.getAnalogButton(R1));
      motorYaxis.run(BACKWARD);
      motorL.run(RELEASE);
      motorR.run(RELEASE);
      motorXaxis.run(RELEASE);

    }

    //DOWN
    if (PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nR2:DOWN "));
      Serial.print(PS3.getAnalogButton(R2));
      motorYaxis.run(FORWARD);
      motorL.run(RELEASE);
      motorR.run(RELEASE);
      motorXaxis.run(RELEASE);

    }

  }
}
