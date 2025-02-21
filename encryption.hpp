#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
class encryption {


public:
std::string getMessage() {return message;}
std::string getEncryptedMessage() {return encrypted_message;}
int getMessageSize() {return message_size;}
int getN() {return n;}
void parse();
void insertInMatrix();
void transposeMatrix();
void sendToFile();
void shiftOperations();
void unParse();


private:
std::string message;
std::string encrypted_message;
int message_size;
int n; // n represents the number of rows and columns of the matrix derived by taking the square root of message_size
std::vector<char> OGparsed;
std::vector<char> ENparsed;
char matrix[n][n];
char matrix_transposed[n][n]



}

#endif
