#include "USBHandler.h"

using namespace MiniKeyboard;

USBHandler::USBHandler(){
  
}

void USBHandler::startConnection(){
    Keyboard.begin();
}

void USBHandler::endConnection(){
   Keyboard.end();
}

void USBHandler::sendKeyStrokes(char **keyCode) {
    while(*keyCode){
		int position = 0;
		while(*((*keyCode)+position) != 0){
			switch((int)*((*keyCode)+position)){ 	// this is a VERY hacky way to detect keycodes within a string. Obscure 
                                                    // ASCII characters that have no use in any key comibation were used to 
                                                    // represent key modifiers, there modifiers overflow the char size and 
                                                    // thus are stored as 2 chars. this is why the negative numbers are used 
                                                    // as cases in the switch statement.
				case -49:// π, Left Windows key
					if(*((*keyCode)+position+1) == -128){
						Keyboard.press(KEY_LEFT_GUI);
						position += 1; // increment keycode to skip the extra char 
						break;	// only break if the key is found otherwise let the switch statement fall to the 
								// default case to be dealt with as a normal key
					}
				case -30:// ∂, Left Control Key
					if(*((*keyCode)+position+1) == -120 && *((*keyCode)+position+2) == -126){
						Keyboard.press(KEY_LEFT_CTRL);
						position += 2;
						break;
					}
				case -61:// Ç, Left Option
					if(*((*keyCode)+position+1) == -121){
						Keyboard.press(KEY_LEFT_ALT);
						position += 1;
						break;
					}
				case -62:// ¥, Left Shift
					if(*((*keyCode)+position+1) == -91){
						Keyboard.press(KEY_LEFT_SHIFT);
						position += 1;
						break;
					}
				default:
					Keyboard.press(*keyCode);
                    Keyboard.releaseAll();
					break;
			}
			position++;
		}
		keyCode++;
	}
}

bool USBHandler::getConnected(){
	return false;
}
