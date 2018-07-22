#include "KeyHandler.h"

using namespace MiniKeyboard;

String keyNamesMac1[NUMBEROFKEYROWS][NUMBEROFKEYCOLUMNS] = {{"200","201","202","203"}, {"210","211","212","213"}, {"220","221","222","223"}, {"230","231","232","233"}};
String keyNamesMac2[NUMBEROFKEYROWS][NUMBEROFKEYCOLUMNS] = {{"300","301","302","303"}, {"310","311","312","313"}, {"320","321","322","323"}, {"330","331","332","333"}};
String keyNamesWindows1[NUMBEROFKEYROWS][NUMBEROFKEYCOLUMNS] = {{"000","001","002","003"}, {"010","011","012","013"}, {"020","021","022","023"}, {"030","031","032","033"}};
String keyNamesWindows2[NUMBEROFKEYROWS][NUMBEROFKEYCOLUMNS] = {{"100","101","102","103"}, {"110","111","112","113"}, {"120","121","122","123"}, {"130","131","132","133"}};
String keyNames[NUMBEROFKEYROWS][NUMBEROFKEYCOLUMNS];
String toSend;

KeyHandler::KeyHandler(){

}
void KeyHandler::selectKeyNames(unsigned char choice){
    switch(choice){
        case 0:
			memcpy(keyNames, keyNamesMac1, sizeof(keyNamesMac1));
        	break;
        case 1:
			memcpy(keyNames, keyNamesMac2, sizeof(keyNamesMac2));
        	break;
        case 2:
			memcpy(keyNames, keyNamesWindows1, sizeof(keyNamesWindows1));
        	break;
        case 3:
			memcpy(keyNames, keyNamesWindows2, sizeof(keyNamesWindows2));
        	break;
    }

}

void KeyHandler::writePressedKeys(bool pressedKeys[NUMBEROFKEYROWS][NUMBEROFKEYCOLUMNS]){
    toSend = "";
    for(int i = 0; i < NUMBEROFKEYROWS; i++){
        for(int n = 0; n < NUMBEROFKEYCOLUMNS; n++){
            if(pressedKeys[i][n]){
                toSend += keyNames[i][n];
            }
        }
    }
	delay(2000);
}
String KeyHandler::getSelectedKeys(){
    return toSend;
}

