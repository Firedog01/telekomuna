#ifndef ZAD2_GLOBAL_CONSTS_H
#define ZAD2_GLOBAL_CONSTS_H

#define SOH 1
#define EOT 4
#define ACK 6
#define NAK 21
#define CAN 24
#define DATA_LENGTH 128
// 3 + 128 + 1
#define PACKET_LENGTH 132
// 3 + 128 + 4
#define PACKET_LENGTH_CRC 135

#endif //ZAD2_GLOBAL_CONSTS_H
