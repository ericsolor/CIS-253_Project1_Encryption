#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <fstream>
#include <string>
#include <vector>

class encryption {
public:
	encryption() : encryption("Hello, world!") {}
	encryption(const std::string& msg);
	int getN() { return n; }
	void parse();
	void insertInMatrix();
	void transposeMatrix();
	void sendToFile();
	void shiftOperations();
	void unParse();

private:
	std::string message;
	std::string encrypted_message;
	int padding = 0;
	int n; // n represents the number of rows and columns of the matrix derived by taking the square root of message_size
	std::vector<std::string> OGparsed;
	std::vector<std::string> ENparsed;
	std::vector<std::vector<std::string>> matrix;
	std::vector<std::vector<std::string>> matrixTransposed;
};

#endif