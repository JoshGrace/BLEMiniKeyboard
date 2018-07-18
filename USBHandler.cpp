#include "USBHandler.h"
#include "Keyboard.h"


#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

MiniKeyboard::USBHandler::USBHandler(){
    
}
void startUSBConnection(){
    Keyboard.begin();
}
void endUSBConnection(){
    //Keyboard.stop();
}
void sendKeyCode(char keyCode) {
    Keyboard.write(keyCode);
}
void sendLines(String keyCode) {
    Keyboard.print(keyCode);
}
bool getUSBConnected(){
	return false;
}