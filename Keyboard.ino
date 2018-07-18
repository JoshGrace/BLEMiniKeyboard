#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "USBHandler.h"
#include "BluetoothHandler.h"
#include "Keyboard.h"

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


  struct key{
    String keyName;
    String keyCode;
    bool pressed;
  };

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

  int verticalPorts [] = {verticalPort0, verticalPort1, verticalPort2, verticalPort3};
  int horizontalPorts [] = {horizontalPort0, horizontalPort1, horizontalPort2, horizontalPort3};

  key pressedKeys[4][4];

  void initKeyCodes();
  void initPorts();
  void readKeys();
  
  BluetoothHandler * bleHan;

    void setup() { 
        initPorts();
        initKeyCodes();
        //open the Serial output port
        Serial.begin(9600);
        // initialize HID Wired Keyboard control:
        Keyboard.begin();
        //MiniKeyboard::USBHandler han = MiniKeyboard::USBHandler();
        //han.startUSBConnection();
        bleHan = new BluetoothHandler();
        bleHan->startBluetooth();
        pinMode(13, OUTPUT);
    }

    void initKeyCodes(){
        pressedKeys[0][0].keyName = "00";
        pressedKeys[0][1].keyName = "01";
        pressedKeys[0][2].keyName = "02";
        pressedKeys[0][3].keyName = "03";
        pressedKeys[1][0].keyName = "10";
        pressedKeys[1][1].keyName = "11";
        pressedKeys[1][2].keyName = "12";
        pressedKeys[1][3].keyName = "13";
        pressedKeys[2][0].keyName = "20";
        pressedKeys[2][1].keyName = "21";
        pressedKeys[2][2].keyName = "22";
        pressedKeys[2][3].keyName = "23";
        pressedKeys[3][0].keyName = "30";
        pressedKeys[3][1].keyName = "31";
        pressedKeys[3][2].keyName = "32";
        pressedKeys[3][3].keyName = "33";
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
        for(int vertPort = 0; vertPort < sizeof(verticalPorts); vertPort++){
            for(int horiPort = 0; horiPort < sizeof(horizontalPorts); horiPort++){
                pressedKeys[vertPort][horiPort].pressed = (digitalRead(verticalPorts[vertPort]) == HIGH 
                    && digitalRead(horizontalPorts[horiPort]) == HIGH);
            }
        }
    }

    void loop() {
      if(bleHan->getBLEConnected()){
          //   // read through the keyboard matrix and if the required ports are on send the related keyboard command
          digitalWrite(13, HIGH);
      } else {
          digitalWrite(13, LOW);
      } 
    }