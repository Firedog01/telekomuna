#include <iostream>
#include "util.h"


using std::cout;
using std::cin;
using std::string;

int main (int argc, char** args)
{
    if (argc == 3) {
        // batch
        string command(args[1]);
        string filename(args[2]);
        if (command == "encode") {
            encodeFile(filename);
        } else if (command == "decode") {
            decodeFile(filename);
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
            } else if (selection == "2") {
                cout << "\nNazwa pliku do odkodowania: ";
                cin >> selection;
				decodeFile(selection);
            } else if (selection == "0") {
                break;
            } else {
                cout << "\bBłędny wybór!\n";
            }
        }
    } else {
        cout << "Użycie: <polecenie (encode/decode)> <plik (ścieżka)>";
        return 1;
    }

    return 0;
}