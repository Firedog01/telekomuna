#include "utility.h"

void send(HANDLE port, std::vector<uint8_t> message) {
//	PurgeComm(port, PURGE_RXCLEAR | PURGE_TXCLEAR);

	DWORD numOfWrittenBytes;
	WriteFile(port,
			  message.data(),
			  message.size(),
			  &numOfWrittenBytes,
			  NULL);
}

uint8_t receiveOne(HANDLE port) {
	uint8_t buffer;
	DWORD numOfReadBytes;
	ReadFile(port,
			 &buffer,
			 1,
			 &numOfReadBytes,
			 NULL);
	return buffer;
}

std::vector<uint8_t> receive(HANDLE port, uint16_t length) {
	std::vector<uint8_t> buffer(length, 0);
	DWORD numOfReadBytes;
	ReadFile(port,
			 buffer.data(),
			 length,
			 &numOfReadBytes,
			 NULL);
	return buffer;
}

uint32_t getChecksum(std::vector<uint8_t> data, bool CRC_enabled) {
	if (CRC_enabled) {
		return CRC16(data);
	} else {
		uint16_t sum = 0;
		for(uint8_t i : data) {
			sum += i;
			sum %= 256;
		}
		return sum;
	}
}

uint32_t CRC16(std::vector<uint8_t> data) {
	uint8_t* ptr = data.data();
	int32_t checksum = 0;
	for (int i = 0; i < data.size(); i++) {
		checksum = checksum ^ (int32_t)*ptr++ << 8;
		for (int j = 0; j < 8; j++) {
			if (checksum & 0x8000) {
				checksum = checksum << 1 ^ 0x11021;
			} else {
				checksum <<= 1;
			}
		}
	}
	checksum = checksum & 0xFFFF;
	return checksum;
}
