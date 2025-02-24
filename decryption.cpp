#include "decryption.hpp"
#include <cmath>
#include <iostream>

decryption::decryption(const std::string& msg, const bool demo) { // constructor for encryption class

	if (demo) { // Confirming it's for demonstration
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
		std::string c(1, ch); // Converting the character into a string
		OGparsed.push_back(c); // Adding the character to the vector
	}

	
	if (demoMode) { // displaying for demo mode
		std::cout << "The message after being parsed: \n\n";
		for (std::string c : OGparsed) {
			std::cout << c << ", ";
		}
		std::cout << std::endl << std::endl;
	}

	padding = std::stoi(OGparsed.back()); // retrieving the amount of added 0's to obtain an nxn matrix
	OGparsed.pop_back(); // removing the coded amount because it is no longer needed

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
void decryption::transposeMatrix() {
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
Primary function responsible for decrypting the message by performing bitwise
shifts right if the current column is even or left if the current column is odd
*///---------------------------------------------------------------------------
void decryption::shiftOperations() {
	for (int i = 0; i < n; i++) { // traversing through rows
		for (int j = 0; j < n; j++) { // traversing through columns
			unsigned char c = static_cast<unsigned char>(matrix[i][j][0]); // Extracting the string character and casting it to an
																		   // unsigned char
			if (j % 2 == 0) { // determing if row is even
				bool lsb = (c & 0x01) != 0; // checking if the right most bit (Least Significant Bit) is 1
				c = (c >> 1); // shifting bits right once
				if (lsb) { // if the LSB is 1
					c |= 0x80; // restore it in the left most position now the Most Significant Bit
				}
			}
			else { // else it is odd
				bool msb = (c & 0x80) != 0; // checking if the left most bit (Most Significant Bit) is 1
				c = (c << 1); // shifting bits left once
				if (msb) { // if the MSB is 1
					c |= 0x01; // restore it in the right most position now the Least Significant Bit
				}
			}
			matrix[i][j] = std::string(1, static_cast<char>(c)); // inserting the shifted character back into the matrix as a string
		}
	}

	if (demoMode) { // displaying for demo mode
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

	for (int i = 0; i < padding; i++) { // removing all the padding added to achieve a perfect square root
		DCparsed.pop_back();
	}

	for (std::string c : DCparsed) { // traversing through every character in vector
		decrypted_message += c; // appending character into the string
	}

	if (demoMode) { // displaying for demo mode
		for (std::string c : DCparsed) {
			std::cout << c << ", ";
		}
		std::cout << std::endl << std::endl;
	}
}

/*------------------------------------------------------------------
This function sends the decrypted message into decrypted_message.txt
*///----------------------------------------------------------------
void decryption::sendToFile() {
	std::ofstream out;
	try { // try catch to ensure file opens properly
		out.open("encrypted_message.txt", std::ios::binary); // opening the file in binary to bit corruption
		if (!out) { // checking if file did not open
			throw std::runtime_error("File could not be opened writing decrypted message to file");
		}
	}
	catch (const std::runtime_error& e) { // file did not open properly
		std::cout << "Error: " << e.what();
		return;
	}

	out << decrypted_message; // sending decrypted message to the file

	out.close(); // closing the file
}