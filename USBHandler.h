#ifndef USBHANDLER_H
#define USBHANDLER_H
#include "Keyboard.h"
namespace MiniKeyboard{
	class USBHandler{
		public:
      		USBHandler();                  // function called the default constructor
			bool getConnected();
	    	void startConnection();
	    	void endConnection();
	    	void sendKeyCode(char );
		    void sendKeyStrokes(char **);
		private:	
	};
}

#endif