#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "USBHandler.h"
#include "BluetoothHandler.h"
#include "KeyHandler.h"

#define USBVoltage 4.22

using namespace MiniKeyboard;

void initPorts();
void readKeys();
void readUserSwitches();
void readConnectionStatusBLE();
void readConnectionStatusUSB();
void readPreferedConnection();
void writeKeys();

enum ConnectionStatuses {USB, BLE, UNCONNECTED};

#endif