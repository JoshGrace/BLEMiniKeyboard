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


void BluetoothHandler::startConnection()
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

void BluetoothHandler::endConnection(){
	ble.disconnect();
  ble.end();
  initialized = false;
}

void BluetoothHandler::sendKeyStrokes(String keyCode)
{
  // for(int i = 0; i < keyCode.length(); i++){
  //       switch((int)keyCode.charAt(i)){
  //           case -49://command π
  //               if(i + 1 < keyCode.length() && ((int)keyCode.charAt(i+1)) == -128){
  //                   Keyboard.press(KEY_LEFT_GUI);
  //                   i++;
  //                   break;// only break if the key is found otherwise let the switch statement fall the the default case
  //                           // to be dealt with2 as a normal key
  //               }
  //           case -30://control ∂
  //               if(i + 1 < keyCode.length() && ((int)keyCode.charAt(i+1)) == -120){
  //                   if(i + 2 < keyCode.length() && ((int)keyCode.charAt(i+2)) == -126){
  //                       Keyboard.press(KEY_LEFT_CTRL);
  //                       i += 2;
  //                       break;// only break if the key is found otherwise let the switch statement fall the the default case
  //                               // to be dealt with as a normal key
  //                   }
  //               }
  //           case -61://left arrow Ç
  //               if(i + 1 < keyCode.length() && ((int)keyCode.charAt(i+1)) == -121){
  //                   Keyboard.press(KEY_LEFT_ARROW);
  //                   i++;
  //                   break;// only break if the key is found otherwise let the switch statement fall the the default case
  //                           // to be dealt with2 as a normal key
  //               }
  //           case -62://option ® / shift ¥
  //               if(i + 1 < keyCode.length() && ((int)keyCode.charAt(i+1)) == -82){// ®
  //                   Keyboard.press(KEY_LEFT_ALT);
  //                   i++;
  //                   break;// only break if the key is found otherwise let the switch statement fall the the default case
  //                           // to be dealt with2 as a normal key
  //               }
  //               if(i + 1 < keyCode.length() && ((int)keyCode.charAt(i+1)) == -91){// ¥
  //                   Keyboard.press(KEY_LEFT_SHIFT);
  //                   i++;
  //                   break;// only break if the key is found otherwise let the switch statement fall the the default case
  //                           // to be dealt with2 as a normal key
  //               }
  //           default:
  //               Keyboard.press(keyCode.charAt(i));
  //               Serial.print((int)keyCode.charAt(i));
  //               break;
  //       }
  //   }
  //   delay(1);
  //   Keyboard.releaseAll();
  // ble.println(toSend);

  ble.print("AT+BleKeyboard=");
  // ble.println(0x0800);
  ble.println("\033");
  ble.waitForOK();

  // ble.print("AT+BleKeyb12340oard=");
  // ble.println('a');
  // ble.waitForOK();4
}

bool BluetoothHandler::getConnected(){
	return ble.isConnected();
}
