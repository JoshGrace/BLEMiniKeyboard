#include "BluetoothHandler.h"

using namespace MiniKeyboard;
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

bool initialized = false;
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

BluetoothHandler::BluetoothHandler(){
  if(!initialized){
    if ( !ble.begin(VERBOSE_MODE) ){
      error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
    }
    ble.echo(false); // Disable command echo from Bluefruit 
    ble.info(); // Print Bluefruit information 
    if (! ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Mini Keyboard" )) ){ // Change the device name to make it easier to find
      error(F("Could not set device name?"));
    }
    if ( !ble.sendCommandCheckOK(F( "AT+HWMODELED=DISABLE" ))){ // Disable LED
      error(F("Could not disable LED"));
    }
    if ( !ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ))){ // Enable HID Service 
      error(F("Could not disable Keyboard"));
    }
    if (! ble.reset() ) { //reset so changes work properly
      error(F("Couldn't reset??"));
    }
    initialized = true;
  }
}


void BluetoothHandler::startBluetooth()
{
  if(initialized){
  //   if ( !ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ))){ // Enable HID Service 
  //    error(F("Could not enable Keyboard"));
  //  }
  //   if (! ble.reset() ) { //reset so changes work properly
    
  //    error(F("Couldn't reset??"));
  //   }
  }
}

void BluetoothHandler::endBluetooth(){
	ble.disconnect();
  ble.end();
  initialized = false;
}

void BluetoothHandler::sendKeyStrokes(String toSend)
{
  // ble.println(toSend);

  ble.print("AT+BleKeyboard=");
  ble.println(toSend);

  ble.waitForOK();

}

bool BluetoothHandler::getBLEConnected(){
	return ble.isConnected();
}
