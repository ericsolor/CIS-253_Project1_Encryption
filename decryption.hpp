#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <fstream>
#include <string>
#include <vector>

class decryption {
public:
	decryption() : decryption("Hello, world!") {}
	decryption(const std::string& msg);
	void parse();
	void insertInMatrix();
	void transposeMatrix();
	void sendToFile();
	void shiftOperations();
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
