#include <iostream>
#include "encryption.hpp"
#include "decryption.hpp"

int main() {
	int userChoice = 0;
	std::string userInput;
	std::string msg, line;
	std::ifstream file;
	std::cout << "Eric Solorzano's Encryption Project \nPlease select a menu option below: \n";
	std::cin >> userChoice;

	switch (userChoice) {
	case 1: // (Encrypt message)
		std::cout << "Please enter path to the message .txt file: ";
		std::getline(std::cin, userInput);
		file.open(userInput);

		while (std::getline(file, line)) {
			msg += line;
		}
		file.close();
		break;
	case 2: // (Decrypt Message)
		break;
	case 3: // (Test)
		break;
	case 4: // (Exit)
		break;
	}
	return 0;
}