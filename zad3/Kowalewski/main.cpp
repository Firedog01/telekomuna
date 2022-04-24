/*#########################################
Autorzy:
Kamil Kowalewski 216806
Jakub Plich 216866
#########################################*/

#include <windows.h>
#include <conio.h>
#include <stdio.h>

bool TG = false;

HANDLE setPort();

DWORD WINAPI Receiver(LPVOID lpParam);

void Transmitter(HANDLE handleSetCOM);

//WYWOLANIE POWYZSZYCH FUNKCJI
int main() {
	
	cout<<"Autorzy:\nKamil Kowalewski 216806\nJakub Plich 216866\n";
	
    //USTAWIANIE PORTU
    DWORD ID = 0;
    HANDLE handleSetCOM = setPort();

    //TWORZENI WATKU I PRZEKAZANIE DO TRANSMITERA
    HANDLE handleThread = CreateThread(NULL, 0, Receiver, handleSetCOM, 0, &ID);
    Transmitter(handleSetCOM);

    //ZAKONCZENIE WATKU ORAZ ZAMKNIECIE UCHWYTU PORTU
    TerminateThread(handleThread, 0);
    CloseHandle(handleSetCOM);
    return 0;
}

//FUNKCJA USTAWIAJACA PORT
HANDLE setPort() {
    int speed = 0;
    int numerOfBits = 8;
    int stopBits = 1;   //DOMYSLNE WARTOSCI DLA PORTU
    int parityBits = 0;
    int portNumber = 1;

    printf("Wybierz portCOM COM [zalecane COM1]:\n"); //WYBOR PORTU
    printf("0. COM1\n");
    printf("1. COM2\n");
    printf("2. COM3\n");
    printf("3. COM4\n");
    printf("Wybor: ");
    scanf("%d", &portNumber); //WCZYTYWANIE WYBORU UZYTKOWNIKA

    if (!(portNumber >= 0 && portNumber <= 3)) { //BLEDNIE PODANE DANE -> WYBOR PORTU COM1
        portNumber = 0;
    }

    char chosenPortNum[5]; // ZAMIANA WYBORU UZYTKOWNIKA NA DANE PROGRAMU
    switch (portNumber) {
        case 0: {
            strcpy(chosenPortNum, "COM1");
            break;
        }
        case 1: {
            strcpy(chosenPortNum, "COM2");
            break;
        }
        case 2: {
            strcpy(chosenPortNum, "COM3");
            break;
        }
        case 3: {
            strcpy(chosenPortNum, "COM4");
            break;
        }
    }

    //TWORZNIE PLIKU
    HANDLE handleSetCOM = CreateFile(chosenPortNum, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    DCB dcbCOM;
    COMMTIMEOUTS timeCOM;

    //WYBOR SZYBKOSCI POLACZENIA
    printf("Wybierz predkosc polaczenia [zalecane 9600]:\n");
    printf("1.  1200\n");
    printf("2.  2400\n");
    printf("3.  4800\n");
    printf("4.  9600\n");
    printf("5. 14400\n");
    printf("6. 19200\n");
    printf("7. 38400\n");
    printf("8. 56000\n");
    printf("9. 57600\n");
    printf("Wybor: ");
    scanf("%d", &speed);//WCZYTYWANIE WYBORU UZYTKOWNIKA

    if (!(speed >= 1 && speed <= 9)) { //BLEDNIE PODANE DANE -> WYBOR 9600
        speed = 4;
    }

    switch (speed) { //USTAWIENIE SZYBKOSCI NA WYBRANA WARTOSC
        case 1: {
            dcbCOM.BaudRate = CBR_1200;
            break;
        }
        case 2: {
            dcbCOM.BaudRate = CBR_2400;
            break;
        }
        case 3: {
            dcbCOM.BaudRate = CBR_4800;
            break;
        }
        case 4: {
            dcbCOM.BaudRate = CBR_9600;
            break;
        }
        case 5: {
            dcbCOM.BaudRate = CBR_14400;
            break;
        }
        case 6: {
            dcbCOM.BaudRate = CBR_19200;
            break;
        }
        case 7: {
            dcbCOM.BaudRate = CBR_38400;
            break;
        }
        case 8: {
            dcbCOM.BaudRate = CBR_56000;
            break;
        }
        case 9: {
            dcbCOM.BaudRate = CBR_57600;
            break;
        }
    }

    dcbCOM.ByteSize = 8; //LICZBY BITOW ROWNA 8
    
    dcbCOM.StopBits = ONESTOPBIT; //JEDEN BIT STOPU
    
    dcbCOM.Parity = NOPARITY; //BEZ PARZYSTOSCI
   
    SetCommState(handleSetCOM, &dcbCOM); //USTAWIENIE PORRTU Z WYBRANYMI PARAMETRAMI

    // USTAWIENIE DODATKOWYCH OPCJI - INTERWAL CZASOWY
    timeCOM.ReadIntervalTimeout = 50;
    timeCOM.ReadTotalTimeoutConstant = 50;
    timeCOM.ReadTotalTimeoutMultiplier = 10;
    timeCOM.WriteTotalTimeoutConstant = 50;
    timeCOM.WriteTotalTimeoutMultiplier = 10;

    // USTAWIENIE TIMEOTOW POLACZENIA
    SetCommTimeouts(handleSetCOM, &timeCOM);

    if (GetCommState(handleSetCOM, &dcbCOM)) { //GETCOMMSTATE == TRUE POLACZENIE STWORZONE POPRAWNIE
        printf("Port COM zainicjalizowany poprawnie\n");
    } else { //GETCOMMSTATE == FALSE POLACZENIE STWORZONE NIEPOPRAWNIE - KONIEC PROGRAMU
        printf("Port COM zainicjalizowany niepoprawnie\n");
        exit(1);
    }
    return handleSetCOM;
}

// FUNKCJA USTAWIA ODBIORNIK
DWORD WINAPI Receiver(LPVOID lpParam) {
    HANDLE &portCOM = (HANDLE &) lpParam;
    char sign = 0;
    DWORD getback = 0;

    while (true) { //PETLA ODCZYTUJE BUFORY Z RAMKI
        if (!TG) {
            ReadFile(portCOM, &sign, 1, &getback, NULL);
            if (getback != 0)
                if (sign != 13)
                    printf("%c", sign);
        } else
            Sleep(10);
    }
}

// FUNKCJA ODPOWIEDZIALNA ZA TRANSMITER
void Transmitter(HANDLE handleSetCOM) {
    char sign = 0;
    DWORD sent = 0;

    do { //PETLA WYKONUJE SIE DO NAPOTKANIA ZNAKU 27 CRLF - KONIEC BIERZACEJ LINII
        sign = getch(); //WCZYTYWANIE ZNAKU
        if (sign != 27) { //JESLI INNY NIZ ENTER
            if (sign != 13) { //WYSWIETL I WYSLIJ
                printf("%c", sign);
                TG = true;
                WriteFile(handleSetCOM, &sign, 1, &sent, NULL);
                TG = false;
            } else {
                printf("\n");
                TG = true;
                sign = 10;
                WriteFile(handleSetCOM, &sign, 1, &sent, NULL);
                sign = 13;
                WriteFile(handleSetCOM, &sign, 1, &sent, NULL);
                TG = false;
            }
        }
        TG = false;
    } while (sign != 27);
}
