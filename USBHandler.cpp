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
void USBHandler::sendKeyStrokes(String keyCode) {
    for(int i = 0; i < keyCode.length(); i++){
        switch((int)keyCode.charAt(i)){
             case -49:
                if(i + 1 < keyCode.length() && ((int)keyCode.charAt(i+1)) == -128){
                    Keyboard.press(KEY_LEFT_GUI);
                    i++;
                    break;// only break if the key is found otherwise let the switch statement fall the the default case
                            // to be dealt with as a normal key
                }
            default:
                Keyboard.press(keyCode.charAt(i));
                Serial.print((int)keyCode.charAt(i));
                break;
        }
    }
    delay(1);
    Keyboard.releaseAll();
}
bool USBHandler::getUSBConnected(){
	return false;
}
