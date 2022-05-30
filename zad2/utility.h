#ifndef ZAD2_UTILITY_H
#define ZAD2_UTILITY_H

#include <windows.h>
#include <cstdint>
#include <vector>

void send(HANDLE port, std::vector<uint8_t> message);
uint8_t receiveOne(HANDLE port);
std::vector<uint8_t> receive(HANDLE port, uint16_t length);
uint32_t getChecksum(std::vector<uint8_t> data, bool CRC_enabled);
uint32_t CRC16(std::vector<uint8_t> data);
#endif //ZAD2_UTILITY_H
