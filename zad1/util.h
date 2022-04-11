#ifndef ZAD1_UTIL_H
#define ZAD1_UTIL_H

#include <vector>
#include <cinttypes>
#include <sstream>
#include <fstream>


typedef std::vector<bool> bitRow;
typedef std::vector<std::vector<bool>> bitMatrix;


bitRow multiplyMatrixByColumn(const bitMatrix& matrix, const bitRow& row);
bitRow encodeBits(const bitRow &word, const bitMatrix &matrix);
bitRow decodeBits(const bitRow &word, const bitMatrix &matrix);

bitRow getBitRow(const bitMatrix& matrix, int idx);
int getSameColIdx(const bitRow& errorVector, const bitMatrix& matrix);
std::pair<int, int> getSameColIdxes(const bitRow& errorVector, const bitMatrix& matrix);

bitRow charToBitRow(char c);
std::string bitRowToStr(bitRow bits);
bitRow strToBitRow(std::string s);
char bitRowToChar(bitRow bits);

void encodeFile(std::string filename);
void decodeFile(std::string filename);

#endif //ZAD1_UTIL_H
