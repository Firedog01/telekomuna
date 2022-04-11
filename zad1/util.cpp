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
	for(const auto & i : matrix) {
		ret.push_back(i[idx]);
	}
	return ret;
}

bitRow getBitColSum(const bitMatrix& matrix, int idx, int idy) {
	bitRow ret = bitRow();
	for(const auto & i : matrix) {
		ret.push_back(i[idx] ^ i[idy]);
	}
	return ret;
}

int getSameColIdx(const bitRow& errorVector, const bitMatrix& matrix) {
	for(int i = 0; i < matrix[0].size(); i++) {
		if (getBitCol(matrix, i) == errorVector) {
			return i;
		}
	}
	return -1;
}

std::pair<int, int> getSameColIdxes(const bitRow& errorVector, const bitMatrix& matrix) {
	for (int i = 0; i < matrix[0].size(); i++) {
		for(int j = i + 1; j < matrix[0].size(); j++) {
			if(getBitColSum(matrix, i, j) == errorVector) {
				return std::make_pair(i, j);
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