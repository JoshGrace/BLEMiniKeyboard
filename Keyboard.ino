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
unsigned char switchSelections;

enum ConnectionStatuses {USB, BLE, UNCONNECTED};
ConnectionStatuses connectionStatus;

const int verticalPorts [] = {verticalPort0, verticalPort1, verticalPort2, verticalPort3};
const int horizontalPorts [] = {horizontalPort0, horizontalPort1, horizontalPort2, horizontalPort3};

bool pressedKeys[4][4] = {{false, false, false, false}, {false, false, false, false}, 
            {false, false, false, false}, {false, false, false, false}};

void initKeyCodes();
void initPorts();
void readKeys();
void readUserSwitches();
void readConnectionStatus();
void writeKeys();
void writeConnectionStatusToLEDs();

BluetoothHandler * bleHan;
KeyHandler * keyHan;
USBHandler * usbHan;

void setup() {
    initPorts();
    connectionStatus = UNCONNECTED;
    //open the Serial output port
    Serial.begin(9600);
    keyHan = new KeyHandler();
    bleHan = new BluetoothHandler();
    bleHan->startBluetooth();
    usbHan = new USBHandler();
    usbHan->startUSBConnection();
}


void loop() {
    readUserSwitches();
    readKeys();
    readConnectionStatus();
    writeConnectionStatusToLEDs();
    writeKeys();

    delay(1000);
}

void initPorts(){// initialize the matrix inputs:
    pinMode(13, OUTPUT);
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
            pressedKeys[vertPort][horiPort] = (digitalRead(verticalPorts[vertPort]) == HIGH && digitalRead(horizontalPorts[horiPort]) == HIGH);
        }
    }
    pressedKeys[0][0] = true;
    pressedKeys[2][3] = true;
    keyHan->writePressedKeys(pressedKeys);
}

void readUserSwitches(){
    switchSelections = 0;
    switchSelections += false;
    switchSelections = switchSelections << 1;
    switchSelections += false;
    keyHan->selectKeyNames(switchSelections);
    defaultToUSB = false;
}

void readConnectionStatus(){
    if(defaultToUSB){// if the user prefers USB
        if(analogRead(A9) * 2 * 3.3 / 1024 > 4.22){// checks if the voltage is over the maximum battery voltage implying that USB is connected
            connectionStatus = USB;
        } else {
            if(bleHan->getBLEConnected()){// if no USB then try bluetooth
                connectionStatus = BLE;
            } else {
                connectionStatus = UNCONNECTED;
            }
        }
    } else {// if the user prefers BLE
        if(bleHan->getBLEConnected()){// check if BLE is actually connected
            connectionStatus = BLE;
        } else {//otherwise try USB
            if(analogRead(A9) * 2 * 3.3 / 1024 > 4.22){// see earlier comment
                connectionStatus = USB;
            } else {
                connectionStatus = UNCONNECTED;
            }
        } 
    }
}

void writeKeys(){
    switch(connectionStatus){
        case USB:
            usbHan->sendKeyStrokes(keyHan->getSelectedKeys());
        	break;
        case BLE:
            bleHan->sendKeyStrokes(keyHan->getSelectedKeys());
        	break;
    }
}

void writeConnectionStatusToLEDs(){
    switch(connectionStatus){
        case USB:
    		digitalWrite(13, HIGH);
        	break;
        case BLE:
    		digitalWrite(13, HIGH);
        	break;
		case UNCONNECTED:
			digitalWrite(13, LOW);
			break;
	}
}