#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <fstream>
#include <string>
#include <vector>

class decryption {
public:
	decryption(const std::string& msg);
	int getN() { return n; }
	void parse();
	void insertInMatrix();
	void shiftOperations();
	void transposeMatrix();
	void sendToFile();
	void unParse();

private:
	std::string message;
	std::string encrypted_message;
	int n; // n represents the number of rows and columns of the matrix derived by taking the square root of message_size
	std::vector<char> OGparsed;
	std::vector<char> DCparsed;
	std::vector<std::vector<char>> matrix;
	std::vector<std::vector<char>> matrixTransposed;
};

#endif
