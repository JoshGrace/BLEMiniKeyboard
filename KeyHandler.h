#ifndef KEYHANDLER_H
#define KEYHANDLER_H
#include <Arduino.h>
//#include <string>

namespace MiniKeyboard{
	class KeyHandler{
	public:
		KeyHandler();                  // function called the default constructor
		~KeyHandler();
		void writePressedKeys(bool[4][4]);
		String getSelectedKeys();

	private:

	};
}

#endif