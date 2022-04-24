#include "../include/ReaderWriter.h"
using namespace std;

ReaderWriter::ReaderWriter(string portName){
	//otwieranie portu
	com = CreateFile(("\\\\.\\" + portName).c_str(),
					 GENERIC_READ | GENERIC_WRITE,
					 0,
					 NULL,
					 OPEN_EXISTING,
					 0,
					 NULL);
	if(com == INVALID_HANDLE_VALUE)
		throw OpeningPortError("Can't open port: " + portName);

	//konfiguracja portu
	DCB dcbSerialParams = {0};
	GetCommState(com, &dcbSerialParams);
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	SetCommState(com, &dcbSerialParams);

	//konfiguracja timeouts
	COMMTIMEOUTS timeouts = {0};
	timeouts.ReadIntervalTimeout = 10;		//in ms
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	SetCommTimeouts(com, &timeouts);
}

void ReaderWriter::write(unsigned char byte){
	DWORD noOfBytesWritten = 0;
	WriteFile(com,
			  &byte,
			  sizeof(byte),
			  &noOfBytesWritten,
			  NULL);
	if(noOfBytesWritten != sizeof(byte)){
		throw ConnectionBrokenError("Can't write byte!");
	}
}

int ReaderWriter::read(){
	unsigned char tmp;
	DWORD noOfBytesRead = 0;
	ReadFile(com,
			 &tmp,
			 sizeof(tmp),
			 &noOfBytesRead,
			 NULL);
	if(noOfBytesRead == 0){
		return -1;
	}
	return tmp;
}

ReaderWriter::~ReaderWriter(){
	CloseHandle(com);
}
