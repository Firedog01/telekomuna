#ifndef ZAD2_SENDER_H
#define ZAD2_SENDER_H

#include <vector>
#include <iostream>
#include <windows.h>
#include <string>

#include "global_consts.h"
#include "utility.h"

class sender {
	bool CRC_enabled;
	HANDLE port;
public:

	bool send_file(std::string filename);
	sender(HANDLE port) : port(port) {}
};


#endif //ZAD2_SENDER_H
