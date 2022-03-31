#include "binary.h"
#include <iostream>
#include <vector>
using namespace std;

BinaryVector multiplyMatrixByVector(const BinaryMatrix& matrix, const BinaryVector& vector){
    BinaryVector result;
    for(BinaryVector row : matrix){
        bool rowResult = 0;
        for(int i = 0; i < row.size(); i++){
            rowResult ^= row[i] & vector[i];
        }
        result.push_back(rowResult);
    }
    return result;
}

BinaryVector codeWord(const BinaryVector& word, const BinaryMatrix& matrix){
    int numberOfParityBits = matrix.size();
    BinaryVector encoded(word);
    encoded.insert(encoded.end(), numberOfParityBits, 0);
    BinaryVector parityBits = multiplyMatrixByVector(matrix, encoded);
    encoded.erase(encoded.end() - numberOfParityBits, encoded.end());
    encoded.insert(encoded.end(), parityBits.begin(), parityBits.end());
    //-----
    //cout << "Kodowanie słowa: " << word << "  --->  " << encoded << endl;
    //-----
    return encoded;
}

BinaryVector decodeWord(const BinaryVector& word, const BinaryMatrix& matrix){
    const int numberOfColumns = 8 + matrix.size();
    const int numberOfRows = matrix.size();
    //create errorVector and check
    BinaryVector errorVector = multiplyMatrixByVector(matrix, word);
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
                        if(matrix[i][j1] ^ matrix[i][j2] != errorVector[i]){
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
    int numberOfParityBits = matrix.size();
    BinaryVector decoded(word);
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

inline BinaryVector convertByteToBinaryVector(byte b){
    BinaryVector vector;
    for(int i = 0; i < 8; i++){
        vector.push_back(b & (1 << (7 - i)));
    }
    return vector;
}

ByteVector codeBytes(const ByteVector& bytes, const BinaryMatrix& matrix){
    //output vectors
    ByteVector outputInBytes;
    BinaryVector outputInBits;
    //code bytes to outputInBits
    for(byte b : bytes){
        BinaryVector encoded = codeWord(convertByteToBinaryVector(b), matrix);
        outputInBits.insert(outputInBits.end(), encoded.begin(), encoded.end());
    }
    //convert outputInBits to outputInBytes
    int counter = 0;
    byte buffer = 0;
    for(bool b : outputInBits){
        buffer += b;
        if(counter == 7){
            outputInBytes.push_back(buffer);
            buffer = 0;
        }
        counter = (counter + 1) % 8;
        buffer <<= 1;
    }
    if(counter != 0){
        buffer <<= 7 - counter;            //filling with zeros
        outputInBytes.push_back(buffer);
    }
    return outputInBytes;
}

ByteVector decodeBytes(const ByteVector& bytes, const BinaryMatrix& matrix){
    //output vectors
    ByteVector outputInBytes;
    int wordLength = 8 + matrix.size();
    //convert bytes to BinaryVector;
    BinaryVector inputInBits;
    for(byte b : bytes){
        BinaryVector bits = convertByteToBinaryVector(b);
        inputInBits.insert(inputInBits.end(), bits.begin(), bits.end());
    }
    //decode input and convert to bytes
    for(unsigned long i = 0; i < inputInBits.size() / wordLength; i++){
        BinaryVector decoded = 
            decodeWord(BinaryVector(inputInBits.begin() + (i * wordLength), inputInBits.begin() + ((i + 1) * wordLength)), matrix);
        byte b = 0;
        for(int j = 0; j < 8; j++){
            b += decoded[j];
            if(j != 8 - 1)
                b <<= 1;
        }
        outputInBytes.push_back(b);
    }
    return outputInBytes;
}

ostream& operator<<(ostream& os, const BinaryVector& vector){
    os << "[";
    for(int i = 0; i < vector.size(); i++){
        os << (int)vector[i];
        if(i != vector.size() - 1)
            cout << " ";
    }
    os << "]";
    return os;
}

ostream& operator<<(ostream& os, const BinaryMatrix& matrix){
    for(int i = 0; i < matrix.size(); i++){
        os << matrix[i];
        if(i != matrix.size() - 1)
            cout << endl;
    }
    return os;
}
