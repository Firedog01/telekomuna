#ifndef READERWRITER_H
#define READERWRITER_H

#include <string>
#include <stdexcept>
#include <windows.h>
using namespace std;

class ReaderWriter{
	HANDLE com;
public:
	ReaderWriter(std::string portName);
	~ReaderWriter();
	//write one byte (or throw exception)
	void write(unsigned char b);
	//try to read one byte (or return -1)
	int read();
};

class OpeningPortError : public std::runtime_error{
public:
	OpeningPortError(const std::string& what_arg) : std::runtime_error(what_arg){}
};
class ConnectionBrokenError : public std::runtime_error{
public:
	ConnectionBrokenError(const std::string& what_arg) : std::runtime_error(what_arg){}
};

#endif //READERWRITER_H
