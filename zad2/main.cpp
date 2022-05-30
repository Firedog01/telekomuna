#include <windows.h>
#include <string>

#include "sender.h"
#include "receiver.h"

using namespace std;

HANDLE portSetup(char* portName);

int main(int argc, char *argv[]) {
//	if(argc != 3)
//		return 1;

	bool enableCRC = false;
	HANDLE port = portSetup(argv[1]);
	int mode = stoi(argv[2]);

//	system("pause");

	if(mode == 1) {
		sender s(port);
		bool good = s.send_file("../message.txt");
		if(!good) {
			cout << "error during transmission, probably malformed packets\n";
			return 3;
		}
		return 0;
	} else if(mode == 2) {
		receiver r(port, enableCRC);
		bool good = r.receive_file("../received.txt");
		if(!good) {
			cout << "could not establish connection\n";
			return 3;
		}
		return 0;
	} else if(mode == 3) {
		while(true);
	}
	return 2;
}

HANDLE portSetup(char* portName) {
	HANDLE port;
	DCB portParams;
	COMMTIMEOUTS portTimeouts = {0};

	port = CreateFile(portName,
							GENERIC_READ | GENERIC_WRITE,
							0,
							nullptr,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							nullptr);

	portParams.DCBlength = sizeof(portParams);
	GetCommState(port, &portParams);

	portParams.BaudRate = CBR_9600;
	portParams.ByteSize = 8;
	portParams.StopBits = ONESTOPBIT;
	portParams.Parity = NOPARITY;
	SetCommState(port, &portParams);

	portTimeouts.ReadIntervalTimeout = 3000;
	portTimeouts.ReadTotalTimeoutMultiplier = 3000;
	portTimeouts.ReadTotalTimeoutConstant = 7000;
	portTimeouts.WriteTotalTimeoutMultiplier = 100;
	portTimeouts.WriteTotalTimeoutConstant = 100;
	SetCommTimeouts(port, &portTimeouts);
	return port;
}