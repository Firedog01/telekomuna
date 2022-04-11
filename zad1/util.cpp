#include <iostream>
#include "util.h"
// 0111010010101111 # T 01010100
bitMatrix H_MATRIX({
        {0, 1, 1, 1, 1, 1, 1, 1,	1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 1, 1, 1, 1,	0, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 1, 1,	0, 0, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 1, 1, 1,	0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 1, 1, 1,	0, 0, 0, 0, 1, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 1, 1,	0, 0, 0, 0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1, 1, 0, 1,	0, 0, 0, 0, 0, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 0,	0, 0, 0, 0, 0, 0, 0, 1},
});


bitRow multiplyMatrixByColumn(const bitMatrix& matrix, const bitRow& row) {
    bitRow result;
    for(bitRow rowMatrix : matrix){
        bool rowResult = false;
        for (int i = 0; i < rowMatrix.size(); i++) {
            rowResult ^= rowMatrix[i] & row[i];
        }
        result.push_back(rowResult);
    }
    return result;
}

bitRow encodeBits(const bitRow &word, const bitMatrix &matrix) {
    int numberOfParityBits = (int) matrix.size();
    bitRow encoded(word);
    encoded.insert(encoded.end(), numberOfParityBits, false);
    bitRow parityBits = multiplyMatrixByColumn(matrix, encoded);
    encoded.erase(encoded.end() - numberOfParityBits, encoded.end());
    encoded.insert(encoded.end(), parityBits.begin(), parityBits.end());
    return encoded;
}

bitRow decodeBits(const bitRow &word, const bitMatrix &matrix) {
	const int numberOfRows = (int) matrix.size();
	const int numberOfColumns = (int) matrix[0].size();
	bitRow decoded(word);
	bitRow errorVector = multiplyMatrixByColumn(matrix, word);

	// if there is any error at least one of bits in vector will be lit up
	auto itErr = errorVector.begin();
	while(itErr != errorVector.end() && !*itErr)
		itErr++;
	if(itErr != errorVector.end()) { // there is some error

		// searching matrix column identical with errorVector
		int errIdx = getSameColIdx(errorVector, matrix);
		if(errIdx != -1) { // one bit error
			std::cout << "korekcja jednego bledu pod indeksem: " << errIdx << '\n';
			decoded[errIdx] = !(decoded[errIdx]);
		} else { // two bit errors
			auto idxes = getSameColIdxes(errorVector, matrix);
			std::cout << "korekcja dwoch bledow\n";
			decoded[idxes.first] = !(decoded[idxes.first]);
			decoded[idxes.second] = !(decoded[idxes.second]);
        }
    }
    decoded.erase(decoded.end() - numberOfRows, decoded.end());
    return decoded;
}

bitRow getBitCol(const bitMatrix& matrix, int idx) {
	bitRow ret = bitRow();
	for (int i = 0; i < matrix.size(); i++) {
		ret.push_back(matrix[i][idx]);
	}
	return ret;
}

bitRow getBitColSum(const bitMatrix& matrix, int idx, int idy) {
	bitRow ret = bitRow();
	for (int i = 0; i < matrix.size(); i++) {
		ret.push_back(matrix[i][idx] ^ matrix[i][idy]);
	}
	return ret;
}

int getSameColIdx(const bitRow& errorVector, const bitMatrix& matrix) {
	bool same;
	for(int j = 0; j < matrix[0].size(); j++) {
		same = true;
		for(int i = 0; i < matrix.size(); i++) {
			if(matrix[i][j] != errorVector[i])
				same = false;
		}
		if(same)
			return j;
	}
	return -1;
}
/*
 *
if(errorBitNumber == -1 && numberOfRows >= 7){
           for(int j1 = 0; j1 < numberOfColumns; j1++){
               bool identical;
               for(int j2 = j1 + 1; j2 < numberOfColumns; j2++){
                   identical = true;
                   for(int i = 0; i < numberOfRows; i++){
                       if((matrix[i][j1] ^ matrix[i][j2]) != errorVector[i]){
                           identical = false;
                           break;
                       }
                   }
                   if(identical){
                       errorBitNumber1 = j1;
                       errorBitNumber2 = j2;
                       break;
                   }
               }
               if(identical){
                   break;
               }
           }
       }
   }

 */
std::pair<int, int> getSameColIdxes(const bitRow& errorVector, const bitMatrix& matrix) {
	for (int i = 0; i < matrix[0].size(); i++) {
		for(int j = i + 1; j < matrix[0].size(); j++) {
			if() {

			}
		}
	}
	return std::make_pair(-1, -1);
}

bitRow charToBitRow(char c) {
    bitRow vector;
	auto it = vector.begin();
    for(int i = 7; i >= 0; i--, it++)
        vector.push_back(c & (1 << i));
    return vector;
}

std::string bitRowToStr(bitRow bits) {
    std::stringstream ss;
    for(bool bit : bits)
        ss << bit;
    return ss.str();
}

bitRow strToBitRow(std::string s) {
    bitRow bits(16);
	auto sit = s.begin();
	auto bitit = bits.begin();
    for(int i = 0; i < 16; i++, sit++, bitit++) {
		bool b = (bool) (*sit - '0');
		*bitit = b;
	}
    return bits;
}

char bitRowToChar(bitRow bits) {
    char c = 0;
    for(int i = 7; i >= 0; i--) {
		c = (char) (c | (bits[7 - i] << i));
	}
    return c;
}

void encodeFile(std::string filename)
{
    std::ifstream file (filename);
    std::ofstream encoded ("../encoded.txt");
    char c;
    if (!file.is_open()) {
        std::cout << "Błędna nazwa pliku do zakodowania!\n";
        return;
    }
    while (file.get(c)) {
        bitRow row = charToBitRow(c);
        row = encodeBits(row, H_MATRIX);
		encoded << bitRowToStr(row) << "\n";
    }
    file.close();
    encoded.close();
    std::cout << "Zakodowany plik: ./encoded.txt\n";
}

void decodeFile(std::string filename)
{
	std::ifstream file (filename);
	std::ofstream decoded ("../decoded.txt");
	std::string line;
    if (!file.is_open()) {
        std::cout << "Błędna nazwa pliku do zdekodowania!\n";
        return;
    }
	while (std::getline(file, line)) {
		if(line == "\n")
			break;
		bitRow row = strToBitRow(line);
		row = decodeBits(row, H_MATRIX);
		decoded << bitRowToChar(row);
	}
	file.close();
	decoded.close();
    std::cout << "Zdekodowany plik: ./decoded.txt\n";
}