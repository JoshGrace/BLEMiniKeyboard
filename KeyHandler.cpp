#include "KeyHandler.h"

using namespace MiniKeyboard;
KeyHandler::KeyHandler(){

}
String keyNames[4][4] = {{"00","01","02","03"}, {"10","11","12","13"}, {"20","21","22","23"}, {"30","31","32","33"}};
String toSend;
void KeyHandler::writePressedKeys(bool pressedKeys[4][4]){
    for(int i = 0; i < sizeof(pressedKeys); i++){
        for(int n = 0; n < sizeof(pressedKeys[i]); n++){
            if(pressedKeys[i][n]){
                toSend += keyNames[i][n];
            }
        }
    }
}
String KeyHandler::getSelectedKeys(){
    return toSend;
}
