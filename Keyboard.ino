#include "Keyboard_INO.h"

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

// set the inputs for the keyboard matrix

const int rowPort0 = 2;
const int rowPort1 = 3;
const int rowPort2 = 4;
const int rowPort3 = 5;
const int columnPort0 = 6;
const int columnPort1 = 7;
const int columnPort2 = 8;
const int columnPort3 = 10;
const int prioritizeUSBPort = 11;
const int isMacPort = 12;
const int hotKeyDepthPort = 13;

bool defaultToUSB;
short switchSelections;

void (*readConnectionStatus)();

ConnectionStatuses connectionStatus;

const int rowPorts [NUMBEROFKEYROWS] = {rowPort0, rowPort1, rowPort2, rowPort3};
const int columnPorts [NUMBEROFKEYCOLUMNS] = {columnPort0, columnPort1, columnPort2, columnPort3};

bool pressedKeys[NUMBEROFKEYROWS][NUMBEROFKEYCOLUMNS] = {{false, false, false, false}, {false, false, false, false}, 
			{false, false, false, false}, {false, false, false, false}};

BluetoothHandler *bleHan;
KeyHandler *keyHan;
USBHandler *usbHan;

void setup() {
	initPorts();
	//open the Serial output port
	Serial.begin(9600);
	keyHan = new KeyHandler();
	bleHan = new BluetoothHandler();
	bleHan->startConnection();
	usbHan = new USBHandler();
	usbHan->startConnection();
}

void loop() {
	readUserSwitches();
	readKeys();
	readPreferedConnection();
	(*readConnectionStatus)();
	writeKeys();
	delay(5000);
}

void initPorts(){// initialize the matrix inputs:
	pinMode(13, OUTPUT);
	pinMode(rowPort0, INPUT);
	pinMode(rowPort1, INPUT);
	pinMode(rowPort2, INPUT);
	pinMode(rowPort3, INPUT);
	pinMode(columnPort0, INPUT);
	pinMode(columnPort1, INPUT);
	pinMode(columnPort2, INPUT);
	pinMode(columnPort3, INPUT);
	pinMode(prioritizeUSBPort, INPUT);
	pinMode(isMacPort, INPUT);
	pinMode(hotKeyDepthPort, INPUT);
}

void readKeys(){
	for(int row = 0; row < NUMBEROFKEYROWS; row++){
		for(int column = 0; column < NUMBEROFKEYCOLUMNS; column++){
			pressedKeys[row][column] = false;// digitalRead(verticalPorts[vertPort]) == HIGH && digitalRead(horizontalPorts[horiPort]) == HIGH;
		}
	}
	pressedKeys[2][0] = true;
}

void readPreferedConnection(){
	defaultToUSB = true;
	if(defaultToUSB){ //digitalRead(verticalPorts[hotKeyDepthPort]) == HIGH
		readConnectionStatus = readConnectionStatusUSB;
	} else {
		readConnectionStatus = readConnectionStatusBLE;
	}
}

void readUserSwitches(){
	switchSelections = 0;
	switchSelections += false;// mac or windows //digitalRead(verticalPorts[isMacPort]) == HIGH
	switchSelections = switchSelections << 1;
	switchSelections += false;// keylayer 1 or 2 //digitalRead(verticalPorts[hotKeyDepthPort]) == HIGH
	keyHan->selectKeyNames(switchSelections);
}

void readConnectionStatusUSB(){
	if(analogRead(A9) * 2 * 3.3 / 1024 > USBVoltage){// checks if the voltage is over the maximum battery voltage implying that USB is connected
		connectionStatus = USB;
	} else if(bleHan->getConnected()){// if no USB then try bluetooth
		connectionStatus = BLE;
	} else {
		connectionStatus = UNCONNECTED;
	}
}

void readConnectionStatusBLE(){
	if(bleHan->getConnected()){// check if BLE is actually connected
		connectionStatus = BLE;
	} else if(analogRead(A9) * 2 * 3.3 / 1024 > USBVoltage){// see earlier comment
		connectionStatus = USB;
	} else {
		connectionStatus = UNCONNECTED;
	}
}

void writeKeys(){
	char *codes[NUMBEROFKEYCOLUMNS * NUMBEROFKEYROWS + 1];
	usbHan->sendKeyStrokes(keyHan->getPressedKeyCodes(pressedKeys, codes));
	switch(connectionStatus){
		case USB:
			// usbHan->sendKeyStrokes(keyHan->getPressedKeyCodes(pressedKeys, codes));
			// digitalWrite(13, HIGH);
			break;
		case BLE:
			// bleHan->sendKeyStrokes(keyHan->getPressedKeyCodes(pressedKeys, codes));
			// digitalWrite(13, HIGH);
			break;
		case UNCONNECTED:
			// digitalWrite(13, LOW);
			break;
	}
}