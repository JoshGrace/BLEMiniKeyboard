#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include <Arduino.h>

#define NUMBEROFKEYROWS 4 // number of key rows on the keyboard
#define NUMBEROFKEYCOLUMNS 4// number of key columns on the MiniKeyboard

namespace MiniKeyboard{

	class KeyHandler{
		public:
			KeyHandler();
			~KeyHandler();
			char **getPressedKeyCodes(bool[NUMBEROFKEYROWS][NUMBEROFKEYCOLUMNS], char**);
			void selectKeyNames(short choice);
		private:

	};
}

#endif