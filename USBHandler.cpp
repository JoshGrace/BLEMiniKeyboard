#include "USBHandler.h"

using namespace MiniKeyboard;
USBHandler::USBHandler(){
    
}
void USBHandler::startUSBConnection(){
    Keyboard.begin();
}
void USBHandler::endUSBConnection(){
   // Keyboard.stop();
}
void USBHandler::sendKeyCode(char keyCode) {
    Keyboard.write(keyCode);
}
void USBHandler::sendKeyStrokes(String keyCode) {
    Keyboard.print(keyCode);
}
bool USBHandler::getUSBConnected(){
	return false;
}