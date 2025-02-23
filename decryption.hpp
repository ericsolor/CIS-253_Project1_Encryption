#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <fstream>
#include <string>
#include <vector>

class decryption {
public:
	decryption(const std::string& msg);
	decryption(const std::string& msg, const bool demo); // activate demo mode
	int getN() { return n; }
	void parse();
	void insertInMatrix();
	void shiftOperations();
	void transposeMatrix();
	void sendToFile();
	void unParse();

private:
	bool demoMode = false;
	std::string message;
	std::string encrypted_message;
	std::string decrypted_message;
	int padding = 0; // number of added 0's to achieve n x n
	int n; // n represents the number of rows and columns of the matrix derived by taking the square root of message_size
	std::vector<std::string> OGparsed; // original parsed message
	std::vector<std::string> DCparsed; // decrypted parsed message
	std::vector<std::vector<std::string>> matrix;
	std::vector<std::vector<std::string>> matrixTransposed;
};

#endif
