#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include <Arduino.h>

#define NUMBEROFKEYROWS 4 // number of key rows on the keyboard
#define NUMBEROFKEYCOLUMNS 4// number of key columns on the keyboard

namespace MiniKeyboard{
	class KeyHandler{
		public:
			KeyHandler();                  // function called the default constructor
			~KeyHandler();
			void writePressedKeys(bool[NUMBEROFKEYROWS][NUMBEROFKEYCOLUMNS]);
			String getSelectedKeys();
			void selectKeyNames(unsigned char choice);
		private:

	};
}

#endif