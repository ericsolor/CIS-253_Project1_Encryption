#include "encryption.hpp"

encryption::encryption(const std::string& msg) { // constructor for encryption class
	message = msg;
	message_size = msg.size();
}

/*-----------------------------------------------------------------
 Parsing the message into individual char characters and populating
 the vector
*///---------------------------------------------------------------
void encryption::parse() {
	for (char c: message) { // Range based for loop to go through each character in message, storing it in c
		OGparsed.push_back(c); // Adding the character to the vector
	}
 
	n = std::ceil(sqrt(OGparsed.size())); // Getting n by taking the square root of the message size wrapped 
										  // in std::ceil to round up to the next whole number

	// filling the vector with 0's to obtain the size n^2
	while (OGparsed.size() < n * n) {
		OGparsed.push_back(0);
	}
}

/*--------------------------------------------------
Inserting the parsed message in the matrix sized nxn
*///------------------------------------------------
void encryption::insertInMatrix() {
	matrix.resize(n, std::vector<char>(n, '0')); // resizing the 2-D vector matrix to n x n and initializing to 0 to
												 // avoid errors
	int index = 0;

	for (int i = 0; i < n; i++) { // navigating through rows of the matrix
		for (int j = 0; j < n; j++) { // navigating through the columns of the matrix
			matrix[i][j] = OGparsed[index]; // inserting char character at index to the matrix in current position
			index++; // increasing index to navigate to the next char
		}
	}
}

