#ifndef ZAD1_UTIL_H
#define ZAD1_UTIL_H

#include <vector>
#include <cinttypes>
#include <sstream>
#include <fstream>


typedef std::vector<bool> bitRow; // we are aware
typedef std::vector<std::vector<bool>> bitMatrix;


bitRow multiplyMatrixByRow(const bitMatrix& matrix, const bitRow& row);
bitRow encodeBits(const bitRow &word, const bitMatrix &matrix);
bitRow decodeBits(const bitRow &word, const bitMatrix &matrix);

bitRow charToBitRow(char c);
std::string bitRowToStr(bitRow bits);
bitRow strToBitRow(std::string s);
char bitRowToChar(bitRow bits);

void encodeFile(std::string filename);
void decodeFile(std::string filename);

#endif //ZAD1_UTIL_H
