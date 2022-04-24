#include <iostream>
#include <fstream>

using namespace std;

// Args: send/receive, port, file
int main(int argc, char** argv) {

    int port;
    char* path;
    ofstream file;

    // Check argc
    if(argc != 3) {
        cerr << "Wrong argc! Help: <send/receive> <port 1-4> <file path>\n";
        return 1;
    }

    // Get port no.
    try {
        port = stoi(argv[1]);
        if (port < 1 || port > 4) cerr << "Wrong port! Help: <port 1-4>\n";
    } catch(exception& e) {
        cerr << "Wrong port! Help: <port 1-4>\n";
    }

    // Get file
    path = argv[2];

    // Get command, file and call function
    if(argv[0] == "send") {
        try {
            file.open(path, ios_base::in);
        } catch(exception& e) {
            cerr << "Invalid file! Help: <file path>\n";
        }
        // TODO: Send
    } else if(argv[0] == "receive") {
        try {
            file.open(path, ios_base::out);
        } catch(exception& e) {
            cerr << "Invalid file! Help: <file path>\n";
        }
        // TODO: Receive
    } else {
        cerr << "Wrong command! Help: <send/receive>\n";
    }

    return 0;
}
