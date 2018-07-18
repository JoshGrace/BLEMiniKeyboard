#ifndef USBHANDLER_H
#define USBHANDLER_H
namespace MiniKeyboard{
	class USBHandler{
	public:
      	USBHandler();                  // function called the default constructor
		bool getUSBConnected();
	    void startUSBConnection();
	    void endUSBConnection();
	    void sendKeyCode(char keyCode);
private:	
	};
}

#endif