#include "USBHandler.h"

using namespace MiniKeyboard;

USBHandler::USBHandler(){
    
}
void USBHandler::startConnection(){
    Keyboard.begin();
}
void USBHandler::endConnection(){
   // Keyboard.stop();
}
void USBHandler::sendKeyStrokes(String keyCode) {
    for(int i = 0; i < keyCode.length(); i++){
        switch((int)keyCode.charAt(i)){
            case -49://command π
                if(i + 1 < keyCode.length() && ((int)keyCode.charAt(i+1)) == -128){
                    Keyboard.press(KEY_LEFT_GUI);
                    i++;
                    break;// only break if the key is found otherwise let the switch statement fall the the default case
                            // to be dealt with2 as a normal key
                }
            case -30://control ∂
                if(i + 1 < keyCode.length() && ((int)keyCode.charAt(i+1)) == -120){
                    if(i + 2 < keyCode.length() && ((int)keyCode.charAt(i+2)) == -126){
                        Keyboard.press(KEY_LEFT_CTRL);
                        i += 2;
                        break;// only break if the key is found otherwise let the switch statement fall the the default case
                                // to be dealt with as a normal key
                    }
                }
            case -61://left arrow Ç
                if(i + 1 < keyCode.length() && ((int)keyCode.charAt(i+1)) == -121){
                    Keyboard.press(KEY_LEFT_ARROW);
                    i++;
                    break;// only break if the key is found otherwise let the switch statement fall the the default case
                            // to be dealt with2 as a normal key
                }
            case -62://option ® / shift ¥
                if(i + 1 < keyCode.length() && ((int)keyCode.charAt(i+1)) == -82){// ®
                    Keyboard.press(KEY_LEFT_ALT);
                    i++;
                    break;// only break if the key is found otherwise let the switch statement fall the the default case
                            // to be dealt with2 as a normal key
                }
                if(i + 1 < keyCode.length() && ((int)keyCode.charAt(i+1)) == -91){// ¥
                    Keyboard.press(KEY_LEFT_SHIFT);
                    i++;
                    break;// only break if the key is found otherwise let the switch statement fall the the default case
                            // to be dealt with2 as a normal key
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
bool USBHandler::getConnected(){
	return false;
}
