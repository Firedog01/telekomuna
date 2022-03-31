#include "util.h"

bitMatrix H_MATRIX {
        {0, 1, 1, 1, 1, 1, 1, 1,	1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 1, 1, 1, 1,	0, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 1, 1,	0, 0, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 1, 1, 1,	0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 1, 1, 1,	0, 0, 0, 0, 1, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 1, 1,	0, 0, 0, 0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1, 1, 0, 1,	0, 0, 0, 0, 0, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 0,	0, 0, 0, 0, 0, 0, 0, 1},
};


bitRow multiplyMatrixByRow(const bitMatrix& matrix, const bitRow& row) {
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
    bitRow parityBits = multiplyMatrixByRow(matrix, encoded);
    encoded.erase(encoded.end() - numberOfParityBits, encoded.end());
    encoded.insert(encoded.end(), parityBits.begin(), parityBits.end());
    //-----
    //cout << "Kodowanie słowa: " << word << "  --->  " << encoded << endl;
    //-----
    return encoded;
}

bitRow decodeBits(const bitRow &word, const bitMatrix &matrix) {
    const int numberOfColumns = 8 + matrix.size();
    const int numberOfRows = (int) matrix.size();
    //create errorVector and check
    bitRow errorVector = multiplyMatrixByRow(matrix, word);
    bool correct = true;
    for(bool b : errorVector){
        if(b){
            correct = false;
            break;
        }
    }
    //-----
    //cout << "errorVector: " << errorVector << endl;
    //-----
    int errorBitNumber = -1;
    int errorBitNumber1 = -1;
    int errorBitNumber2 = -1;
    if(!correct){
        //searching matrix column identical with errorVector
        for(int j = 0; j < numberOfColumns; j++){
            bool identical = true;
            for(int i = 0; i < numberOfRows; i++){
                if(matrix[i][j] != errorVector[i]){
                    identical = false;
                    break;
                }
            }
            if(identical){
                errorBitNumber = j;
                break;
            }
        }
        //searching matrix columns which sum equals errorVector
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
    //decode and repair
    int numberOfParityBits = (int) matrix.size();
    bitRow decoded(word);
    if(errorBitNumber != -1){
        //korekcja jednego błędu
        decoded[errorBitNumber] = !decoded[errorBitNumber];
    }else if(errorBitNumber1 != -1 && errorBitNumber2 != -1){
        //korekcja dwóch błędów
        decoded[errorBitNumber1] = !decoded[errorBitNumber1];
        decoded[errorBitNumber2] = !decoded[errorBitNumber2];
    }
    decoded.erase(decoded.end() - numberOfParityBits, decoded.end());
    //-----
    //cout << "Dekodowanie słowa: " << word << "  --->  " << decoded << endl;
    //-----
    return decoded;
}

std::string encodeByte(char c) {
    bitRow bits = charToBitRow(c);
    bitRow encoded = encodeBits(bits, H_MATRIX);
    return bitRowToStr(encoded);
}

char decodeByte(std::string encoded) {

}

bitRow charToBitRow(char c) {
    bitRow vector(8);
    for(int i = 7; i >= 0; i--)
        vector.push_back(c & (1 << i) );
    return vector;
}

std::string bitRowToStr(bitRow bits) {
    std::stringstream ss;
    for(bool bit : bits)
        ss << ('0' + (char) bit);
    return ss.str();
}

bitRow strToBitRow(std::string s) {
    bitRow bits(8);
    auto it = s.begin();
    auto bitit = bits.begin();
    for(int i = 0; i < 8; i++, it++, bitit++)
        *bitit = (bool) (*it - '0');
    return bits;
}

char bitRowToChar(bitRow bits) {
    char c = 0;
    bitRow::iterator itbit = bits.begin();
    for(int i = 7; i >= 0; i--)
        c |= (itbit[7 - i]) << i;
    return c;
}

void encodeFile(const std::string& filename)
{
    std::ifstream file (filename);
    std::ofstream encoded ("../encoded.txt");
    char c;
    while (file.get(c)) {
        bitRow row = charToBitRow(c);
        row = encodeBits(row, H_MATRIX);
    }
    file.close();
    encoded.close();
}

void decodeFile(const std::string& filename)
{

}