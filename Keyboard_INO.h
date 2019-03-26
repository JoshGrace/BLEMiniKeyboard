#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "USBHandler.h"
#include "BluetoothHandler.h"
#include "KeyHandler.h"

#define USBVoltage 4.22

using namespace MiniKeyboard;

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

void initPorts();
void readKeys();
void readUserSwitches();
void readConnectionStatusBLE();
void readConnectionStatusUSB();
void readPreferedConnection();
void writeKeys();
void (*readConnectionStatus)();
#endif