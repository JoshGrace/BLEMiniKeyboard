#ifndef KEYHANDLER_H
#define KEYHANDLER_H
//#include <string>

namespace MiniKeyboard{
	class KeyHandler{
	public:
		KeyHandler();                  // function called the default constructor
		~KeyHandler();
		void writePressedKeys(bool[4][4]);
//		std::string getSelectedKeys();
//std::string josh;

	private:

	};
}

#endif