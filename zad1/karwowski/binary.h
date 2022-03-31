#include <vector>
#include <iostream>

typedef std::vector<bool> BinaryVector;
typedef std::vector<std::vector<bool>> BinaryMatrix;
typedef unsigned char byte;
typedef std::vector<byte> ByteVector;

BinaryVector multiplyMatrixByVector(const BinaryMatrix& matrix, const BinaryVector& vector);

BinaryVector encodeBits(const BinaryVector& word, const BinaryMatrix& matrix);

BinaryVector decodeBits(const BinaryVector& word, const BinaryMatrix& matrix);

ByteVector codeBytes(const ByteVector& bytes, const BinaryMatrix& matrix);

ByteVector decodeBytes(const ByteVector& bytes, const BinaryMatrix& matrix);

std::ostream& operator<<(std::ostream& os, const BinaryVector& vector);
std::ostream& operator<<(std::ostream& os, const BinaryMatrix& matrix);
