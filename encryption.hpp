#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <fstream>
#include <string>
#include <vector>

class encryption {
public:
	encryption() : encryption("Hello, world!", true) {} // default constructor, activating demo mode
	encryption(const std::string& msg, bool demo = false);
	int getN() { return n; }
	bool getDemoMode() { return demoMode; }
	void parse();
	void insertInMatrix();
	void transposeMatrix();
	void sendToFile();
	void shiftOperations();
	void unParse();

private:
	bool demoMode = false;
	std::string message;
	std::string encrypted_message;
	int padding = 0; // number of added 0's to achieve n x n
	int n; // n represents the number of rows and columns of the matrix derived by taking the square root of message_size
	std::vector<std::string> OGparsed; // original parsed message
	std::vector<std::string> ENparsed; // encrypted parsed message
	std::vector<std::vector<std::string>> matrix;
	std::vector<std::vector<std::string>> matrixTransposed;
};

#endif