#include "binary.h"
#include "kod1.h"
#include "kod2.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(int n, char** args){
    if(n != 3){
        cout << "using: code/decode filename" << endl;
        return 0;
    }
    string command(args[1]);
    string filename(args[2]);
    ifstream is(filename, ios::binary);
    ByteVector bytes;
    if(!is){
        cout << "Unknown file!" << endl;
        return 0;
    }else{
        while(is){
            byte b = is.get();
            if(is)
                bytes.push_back(b);
        }
    }
    if(command == "code"){
        ByteVector encoded = codeBytes(bytes, H2);
        ofstream os("encoded", ios::binary);
        for(byte b : encoded){
            os.put(b);
        }
        os.close();
    }else if(command == "decode"){
        ByteVector decoded = decodeBytes(bytes, H2);
        ofstream os("decoded", ios::binary);
        for(byte b : decoded){
            os.put(b);
        }
        os.close();
    }else{
        cout << "Unknown command!" << endl;
    }
    is.close();
}
