#ifndef ZAD2_RECEIVER_H
#define ZAD2_RECEIVER_H

#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "global_consts.h"
#include "utility.h"

class receiver {
	bool CRC_enabled = false;
	HANDLE port;
public:
	bool receive_file(std::string filename);
	receiver(HANDLE port, bool enableCRC) : port(port), CRC_enabled(enableCRC) {}
};


#endif //ZAD2_RECEIVER_H
