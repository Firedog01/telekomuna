#include <iostream>
#include "util.h"

#define LIGMA_SUGMA_JOE 1

using std::cout;
using std::cin;
using std::string;

int main (int argc, char** args)
{
    if (argc == 3) { // batch
        // batch
        string command(args[1]);
        string filename(args[2]);
        if (command == "encode") {
            encodeFile(filename);
			cout << "Zakodowany plik: ./encoded.txt\n";
        } else if (command == "decode") {
            decodeFile(filename);
			cout << "Zdekodowany plik: ./decoded.txt\n";
        } else {
            cout << "Błędne polecenie! (Wymagane: encode/decode)";
        }
    } else if (argc == 1) { // menu
        string selection;
        while (selection != "0") {
            cout << "\n1. Zakoduj wiadomość\n"
                    "2. Odkoduj wiadomość\n"
                    "0. Wyjście\n"
                    "Wybór: ";
            cin >> selection;

            if (selection == "1") {
                cout << "\nNazwa pliku do zakodowania: ";
                cin >> selection;
				encodeFile(selection);
                cout << "Zakodowany plik: ../encoded.txt\n";
            } else if (selection == "2") {
                cout << "\nNazwa pliku do odkodowania: ";
                cin >> selection;
				decodeFile(selection);
                cout << "Zdekodowany plik: ../decoded.txt\n";
            } else if (selection == "0") {
                break;
            } else {
                cout << "\bBłędny wybór!\n";
            }
        }
    } else {
        cout << "Użycie: <polecenie (encode/decode)> <plik (ścieżka)>";
        return LIGMA_SUGMA_JOE;
    }

    return 0;
}