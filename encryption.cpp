#include "encryption.hpp"
#include <cmath>
#include <iostream>

encryption::encryption(const std::string& msg, bool demo) { // constructor for encryption class

	if (demo) { // checking if it's in demo mode
		std::cout << "\nNow Encrypting 'Hello, world!'... \n\n";
		demoMode = demo;
	}

	message = msg;
	parse();
	insertInMatrix();
	transposeMatrix();
	shiftOperations();
	unParse();
	sendToFile();
}

/*-----------------------------------------------------------------
 Parsing the message into individual char characters and populating
 the vector
*///---------------------------------------------------------------
void encryption::parse() {
	for (char ch: message) { // Range based for loop to go through each character in message, storing it in c
		std::string c(1, ch);
		OGparsed.push_back(c); // Adding the character to the vector
	}
 
	n = std::ceil(std::sqrt(OGparsed.size())); // Getting n by taking the square root of the message size wrapped 
											   // in std::ceil to round up to the next whole number

	// filling the vector with 0's to obtain the size n^2
	while (OGparsed.size() < n * n) {
		OGparsed.push_back("0");
		padding++; // keeping track of how many 0's are added for padding
	}

	if (demoMode) { // displaying for demo mode
		std::cout << "The message after being parsed and filled to make its size a perfect square root: \n\n";
		for (std::string c : OGparsed) {
			std::cout << c << ", ";
		}
		std::cout << std::endl << std::endl;
	}
}

/*--------------------------------------------------
Inserting the parsed message in the matrix sized nxn
*///------------------------------------------------
void encryption::insertInMatrix() {
	matrix.resize(n, std::vector<std::string>(n, "0")); // resizing the 2-D vector matrix to n x n and initializing to 0 to
														// avoid errors
	int index = 0;

	for (int i = 0; i < n; i++) { // navigating through rows of the matrix
		for (int j = 0; j < n; j++) { // navigating through the columns of the matrix
			matrix[i][j] = OGparsed[index]; // inserting char character at index to the matrix in current position
			index++; // increasing index to navigate to the next char
		}
	}

	if (demoMode) { // displaying for demo mode
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
void encryption::transposeMatrix() {
	matrixTransposed.resize(n, std::vector<std::string>(n, "0")); // resizing the 2-D vector to n x n and initializing it to zero

	for (int i = 0; i < n; i++) { // traversing through the rows
		for (int j = 0; j < n; j++) { // traversing through the columns
			matrixTransposed[i][j] = matrix[j][i]; // using the definition of transposing a matrix
		}
	}

	if (demoMode) { // displaying for demo mode
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

/*-----------------------------------------------------------------------------
Primary function responsible for encrypting the message by performing bitwise
shifts right if the current column is even or left if the current column is odd
*///---------------------------------------------------------------------------
void encryption::shiftOperations() {
	for (int i = 0; i < n; i++) { // traversing through rows
		for (int j = 0; j < n; j++) { // traversing through columns
			unsigned char c = static_cast<unsigned char>(matrixTransposed[i][j][0]); // Extracting the string character and casting it to an
																					 // unsigned char
			if (j % 2 == 0) { // determing if row is even
				bool msb = (c & 0x80) != 0; // checking if the left most bit (Most Significant Bit) is 1
				c = (c << 1); // shifting bits left once
				if (msb) { // if the MSB is 1
					c |= 0x01; // restore it in the right most position now the Least Significant Bit
				}
			}
			else { // else it is odd
				bool lsb = (c & 0x01) != 0; // checking if the right most bit (Least Significant Bit) is 1
				c = (c >> 1); // // shifting bits right once
				if (lsb) { // if the LSB is 1
					c |= 0x80; // restore it in the left most position now the Most Significant Bit
				}
			}
			matrixTransposed[i][j] = std::string(1, static_cast<char>(c)); // inserting the shifted character back into the matrix as a string
		}
	}

	if (demoMode) { // displaying for demo mode
		std::cout << "The message after it has been shifted: \n\n";
		for (int i = 0; i < n; i++) { // navigating through rows of the matrix
			for (int j = 0; j < n; j++) { // navigating through the columns of the matrix
				std::cout << matrixTransposed[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

}

/*---------------------------------------------------------------------
This function is to unparse the matrix into a vector then into a string
*///-------------------------------------------------------------------
void encryption::unParse() {

	for (int i = 0; i < n; i++) { // traversing through rows
		for (int j = 0; j < n; j++) { // traversing through columns
			ENparsed.push_back(matrixTransposed[i][j]); // inserting characters from current position in matrix to vector
		}
	}

	for (std::string c : ENparsed) { // traversing through every character in vector
		encrypted_message += c; // appending character into the string
	}

	if (demoMode) { // displaying for demo mode
		std::cout << "Message after it has been extracted from the matrix: \n\n";
		for (std::string c : ENparsed) {
			std::cout << c << ", ";
		}
		std::cout << std::endl << std::endl;
	}
}

/*----------------------------------------------------------
This function sends the encrypted message into encrypted_message.txt
*///--------------------------------------------------------
void encryption::sendToFile() {
	std::ofstream out("encrypted_message.txt", std::ios::binary); // opening the file in binary to bit corruption
	out << encrypted_message << std::to_string(padding); // sending encrypted message to the file

	out.close(); // closing the file
}