#include "KeyHandler.h"

using namespace MiniKeyboard;
//π = command
//∂ = control
//Ç = left arrow
//® = option
//¥ = shift
char *keyNamesWindows1[NUMBEROFKEYROWS][NUMBEROFKEYCOLUMNS] =   {{"000","001","002","003"}, {"010","011","012","013"}, 
                                                                {"hello","021","022","023"}, {"030","031","032","033"}};
char *keyNamesWindows2[NUMBEROFKEYROWS][NUMBEROFKEYCOLUMNS] =   {{"100","101","102","103"}, {"110","111","112","113"}, 
                                                                {"120","121","122","123"}, {"130","131","132","133"}};
char *keyNamesMac1[NUMBEROFKEYROWS][NUMBEROFKEYCOLUMNS] =   {{"πa","∂Ç","®πu","¥Ç"}, {"210","211","212","213"}, 
                                                            {"220","221","222","223"}, {"230","231","232","233"}};
char *keyNamesMac2[NUMBEROFKEYROWS][NUMBEROFKEYCOLUMNS] =   {{"300","301","302","303"}, {"310","311","312","313"}, 
                                                            {"320","321","322","323"}, {"330","331","332","333"}};

char *pressedKeyCodes[NUMBEROFKEYROWS * NUMBEROFKEYCOLUMNS + 1];

char ***keyNames;

KeyHandler::KeyHandler(){

}

void KeyHandler::selectKeyNames(short choice){
    switch(choice){
        case 0:
            keyNames = (char ***)keyNamesWindows1;
        	break;
        case 1:
            keyNames = (char ***)keyNamesWindows2;
        	break;
        case 2:
            keyNames = (char ***)keyNamesMac1;
        	break;
        case 3:
            keyNames = (char ***)keyNamesMac2;
        	break;
    }
}

char **KeyHandler::getPressedKeyCodes(bool pressedKeys[NUMBEROFKEYROWS][NUMBEROFKEYROWS], char **toSend){
    char **codes = toSend;
    for(int i = 0; i < NUMBEROFKEYROWS; i++){
        for(int n = 0; n < NUMBEROFKEYCOLUMNS; n++){
            if(pressedKeys[i][n]){
                 *(codes++) = keyNames[i][n];
            }
        }
    }
    *(codes) = 0;
    return toSend;
}