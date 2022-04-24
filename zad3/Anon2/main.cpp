#include <windows.h>
#include <conio.h>
#include <stdio.h>

bool flag = false;

HANDLE setPort();
DWORD WINAPI Receiver(LPVOID lpParam);
void Transmitter(HANDLE handleSetCOM);

int main() {
	DWORD ID = 0;
	HANDLE handleSetCOM = setPort(); //ustawianie portu

	HANDLE handleThread = CreateThread(NULL, 0, Receiver, handleSetCOM, 0, &ID);
	Transmitter(handleSetCOM);

	TerminateThread(handleThread, 0); //zamkniecie watku
	CloseHandle(handleSetCOM);
	return 0;
}

HANDLE setPort() {
	int speed = 0;
	int numerOfBits = 8;
	int stopBits = 1;
	int parityBits = 0;
	int portNumber = 1;

	char chosenPortNum[5];

	strcpy(chosenPortNum, "COM1");

	HANDLE handleSetCOM = CreateFile(chosenPortNum, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL); //tworzenie pliku
	DCB dcbCOM;
	COMMTIMEOUTS timeCOM;

	dcbCOM.BaudRate = CBR_9600;

	dcbCOM.ByteSize = 8;

	dcbCOM.StopBits = ONESTOPBIT; //stop

	dcbCOM.Parity = NOPARITY; //parzystosc

	SetCommState(handleSetCOM, &dcbCOM);

	timeCOM.ReadIntervalTimeout = 50;
	timeCOM.ReadTotalTimeoutConstant = 50;
	timeCOM.ReadTotalTimeoutMultiplier = 10; //parametry
	timeCOM.WriteTotalTimeoutConstant = 50;
	timeCOM.WriteTotalTimeoutMultiplier = 10;

	SetCommTimeouts(handleSetCOM, &timeCOM);

	if (GetCommState(handleSetCOM, &dcbCOM)) {
		printf("Polaczono COM port\n");
	} else {
		printf("Blad COM port\n");
		exit(1);
	}
	return handleSetCOM;
}

DWORD WINAPI Receiver(LPVOID lpParam) {
	HANDLE &portCOM = (HANDLE &) lpParam;
	char sign = 0;
	DWORD getback = 0;

	while (true) {
		if (!flag) {
			ReadFile(portCOM, &sign, 1, &getback, NULL);
			if (getback != 0)
				if (sign != 13)
					printf("%c", sign);
		} else
			Sleep(10);
	}
}

void Transmitter(HANDLE handleSetCOM) {
	char sign = 0;
	DWORD sent = 0;

	do {
		sign = getch();
		if (sign != 27) { //27 esc //13enter //10space
			if (sign != 13) {
				printf("%c", sign);
				flag = true;
				WriteFile(handleSetCOM, &sign, 1, &sent, NULL);
				flag = false;
			} else {
				printf("\n");
				flag = true;
				sign = 10;
				WriteFile(handleSetCOM, &sign, 1, &sent, NULL);
				sign = 13;
				WriteFile(handleSetCOM, &sign, 1, &sent, NULL);
				flag = false;
			}
		}
		flag = false;
	} while (sign != 27);
}
