#include "USBHandler.h"
#include "BluetoothHandler.h"
#include "KeyHandler.h"

/*
  Keyboard layout is
  |-|-|-|-|-|
  |-|1|2|3|-|-horizontalPort0
  |-|4|5|6|-|-horizontalPort2
  |-|7|8|9|-|-horizontalPort2
  |-|-|-|-|-|
     |vertical1
       |verticalPort1
         |verticalPort2 
*/

using namespace MiniKeyboard;

// set the inputs for the keyboard matrix
const int verticalPort0 = 2;
const int verticalPort1 = 3;
const int verticalPort2 = 4;
const int verticalPort3 = 5;
const int horizontalPort0 = 6;
const int horizontalPort1 = 7;
const int horizontalPort2 = 8;
const int horizontalPort3 = 9;
const int prioritizeUSBPort = 10;
const int isMacPort = 11;
const int hotKeyDepthPort = 12;

bool defaultToUSB;

int verticalPorts [] = {verticalPort0, verticalPort1, verticalPort2, verticalPort3};
int horizontalPorts [] = {horizontalPort0, horizontalPort1, horizontalPort2, horizontalPort3};

bool pressedKeys[4][4] = {{false, false, false, false}, {false, false, false, false}, {false, false, false, false}, {false, false, false, false}};

void initKeyCodes();
void initPorts();
void readKeys();
  
BluetoothHandler * bleHan;
KeyHandler * keyHan;

void setup() { 
    defaultToUSB = false;
    initPorts();
    //open the Serial output port
    Serial.begin(9600);
    // initialize HID Wired Keyboard control:
    //Keyboard.begin();
    keyHan = new KeyHandler();
    bleHan = new BluetoothHandler();
    bleHan->startBluetooth();
    pinMode(13, OUTPUT);
}


    void initPorts(){// initialize the matrix inputs:
        pinMode(verticalPort0, INPUT);
        pinMode(verticalPort1, INPUT);
        pinMode(verticalPort2, INPUT);
        pinMode(verticalPort3, INPUT);
        pinMode(horizontalPort0, INPUT);
        pinMode(horizontalPort1, INPUT);
        pinMode(horizontalPort2, INPUT);
        pinMode(horizontalPort3, INPUT);
        pinMode(prioritizeUSBPort, INPUT);
        pinMode(isMacPort, INPUT);
        pinMode(hotKeyDepthPort, INPUT);
    }

    void readKeys(){
        for(int vertPort = 0; vertPort < (sizeof(pressedKeys)/sizeof(pressedKeys)[vertPort]); vertPort++){
            for(int horiPort = 0; horiPort < (sizeof(pressedKeys[vertPort])/sizeof(pressedKeys[vertPort][horiPort])); horiPort++){
                pressedKeys[vertPort][horiPort] = false;// = (digitalRead(verticalPorts[vertPort]) == HIGH 
                    //&& digitalRead(horizontalPorts[horiPort]) == HIGH);
            }
        }
        pressedKeys[0][0] = true;
        pressedKeys[2][3] = true;
        keyHan->writePressedKeys(pressedKeys);
    }

void loop() {
    readKeys();
    if(defaultToUSB){// if the user prefers USB
        if(analogRead(A9) * 2 * 3.3 / 1024 > 4.22){// checks if the voltage is over the maximum battery voltage
                                                // implying that USB is connected
           // digitalWrite(13, HIGH);
        } else {
            if(bleHan->getBLEConnected()){// if no USB then try bluetooth
          ///      digitalWrite(13, HIGH);
                delay(250);
            }
            digitalWrite(13, LOW);
        }
    } else {// if the user prefers BLE
        if(bleHan->getBLEConnected()){// check if BLE is actually connected
            bleHan->sendKeyStrokes(keyHan->getSelectedKeys());
        } else {//otherwise try BLE
            if(analogRead(A9) * 2 * 3.3 / 1024 > 4.22){// see earlier comment
              //  digitalWrite(13, HIGH);
                delay(250);
            } 
            //digitalWrite(13, HIGH);
        } 
    }
    
    delay(250);
}