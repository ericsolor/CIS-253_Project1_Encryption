#include "decryption.hpp"
#include <cmath>
#include <iostream>

decryption::decryption(const std::string& msg, const bool demo) { // constructor for encryption class

	if (demo) {
		std::cout << "\nNow Decrypting '" << msg << "'... \n\n";
		demoMode = demo;
		encrypted_message = msg;
		parse();
		insertInMatrix();
		shiftOperations();
		transposeMatrix();
		unParse();
		sendToFile();
	}
	else {
		std::cout << "Something went really wrong somewhere. Accessing Demo Mode while false?\n\n";
	}
}

decryption::decryption(const std::string& msg) { // constructor for encryption class
	encrypted_message = msg;
	parse();
	insertInMatrix();
	shiftOperations();
	transposeMatrix();
	unParse();
	sendToFile();
}

/*-----------------------------------------------------------------
 Parsing the message into individual char characters and populating
 the vector
*///---------------------------------------------------------------
void decryption::parse() {
	for (char ch : encrypted_message) { // Range based for loop to go through each character in message, storing it in c
		std::string c(1, ch);
		OGparsed.push_back(c); // Adding the character to the vector
	}

	
	if (demoMode) {
		std::cout << "The message after being parsed: \n\n";
		for (std::string c : OGparsed) {
			std::cout << c << ", ";
		}
		std::cout << std::endl << std::endl;
	}

	padding = std::stoi(OGparsed.back());
	OGparsed.pop_back();

	n = std::ceil(std::sqrt(OGparsed.size())); // Getting n by taking the square root of the message size wrapped 
	// in std::ceil to round up to the next whole number
}

/*--------------------------------------------------
Inserting the parsed message in the matrix sized nxn
*///------------------------------------------------
void decryption::insertInMatrix() {
	matrix.resize(n, std::vector<std::string>(n, "0")); // resizing the 2-D vector matrix to n x n and initializing to 0 to
												 // avoid errors
	int index = 0;

	for (int i = 0; i < n; i++) { // navigating through rows of the matrix
		for (int j = 0; j < n; j++) { // navigating through the columns of the matrix
			matrix[i][j] = OGparsed[index]; // inserting char character at index to the matrix in current position
			index++; // increasing index to navigate to the next char
		}
	}

	if (demoMode) {
		std::cout << "The message after it has been inserted into the matrix: \n\n";
		for (int i = 0; i < n; i++) { // navigating through rows of the matrix
			for (int j = 0; j < n; j++) { // navigating through the columns of the matrix
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

/*--------------------------------------------------------------------------
Transposing the original matrix using matrixTransposed as the updated matrix
*///------------------------------------------------------------------------
void decryption::transposeMatrix() {
	matrixTransposed.resize(n, std::vector<std::string>(n, "0")); // resizing the 2-D vector to n x n and initializing it to zero

	for (int i = 0; i < n; i++) { // traversing through the rows
		for (int j = 0; j < n; j++) { // traversing through the columns
			matrixTransposed[i][j] = matrix[j][i]; // using the definition of transposing a matrix
		}
	}

	if (demoMode) {
		std::cout << "The message after it has been transposed: \n\n";
		for (int i = 0; i < n; i++) { // navigating through rows of the matrix
			for (int j = 0; j < n; j++) { // navigating through the columns of the matrix
				std::cout << matrixTransposed[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

/*---------------------------------------------------------------------------
Primary function responsible for encrypting the message by performing bitwise
operations on the matrix rotating bits left if the current column is even or
rotating bits right if the current column is odd
*///-------------------------------------------------------------------------
void decryption::shiftOperations() {
	for (int i = 0; i < n; i++) { // traversing through rows
		for (int j = 0; j < n; j++) { // traversing through columns
			unsigned char c = static_cast<unsigned char>(matrix[i][j][0]);
			if (j % 2 == 0) { // determing if row is even
				bool lsb = (c & 0x01) != 0;
				c = (c >> 1); // rotating bits right
				if (lsb) {
					c |= 0x08;
				}
			}
			else { // else it is odd
				bool msb = (c & 0x80) != 0;
				c = (c << 1); // rotating bits left
				if (msb) {
					c |= 0x01;
				}
			}
			matrix[i][j] = std::string(1, static_cast<char>(c));
		}
	}

	if (demoMode) {
		std::cout << "The message after it has been shifted: \n\n";
		for (int i = 0; i < n; i++) { // navigating through rows of the matrix
			for (int j = 0; j < n; j++) { // navigating through the columns of the matrix
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

}

/*---------------------------------------------------------------------
This function is to unparse the matrix into a vector then into a string
*///-------------------------------------------------------------------
void decryption::unParse() {

	for (int i = 0; i < n; i++) { // traversing through rows
		for (int j = 0; j < n; j++) { // traversing through columns
			DCparsed.push_back(matrixTransposed[i][j]); // inserting characters from current position in matrix to vector
		}
	}

	for (int i = 0; i < padding; i++) {
		DCparsed.pop_back();
	}

	for (std::string c : DCparsed) { // traversing through every character in vector
		decrypted_message += c; // appending character into the string
	}

	if (demoMode) {
		for (std::string c : DCparsed) {
			std::cout << c << ", ";
		}
		std::cout << std::endl << std::endl;
	}
}

/*----------------------------------------------------------
This function sends the encrypted message into encrypted.txt
*///--------------------------------------------------------
void decryption::sendToFile() {
	std::ofstream out("decrypted_message.txt", std::ios::binary); // opening the file (most likely creating a new file)

	out << decrypted_message; // sending encrypted message to the file

	out.close(); // closing the file
}