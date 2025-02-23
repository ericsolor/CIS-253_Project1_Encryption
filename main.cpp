#include <iostream>
#include "encryption.hpp"
#include "decryption.hpp"

int main() {
	int userChoice = 0;
	std::string userInput;
	std::string msg, line;
	std::ifstream file;
	std::cout << "Eric Solorzano's Encryption Project \nPlease select a menu option below: \n";

	std::cout << "Input: ";
	std::cin >> userChoice;
	std::cin.ignore();

	while (userChoice != 4) {
			switch (userChoice) {
			case 1: { // (Encrypt message)
				msg.clear();
				std::cout << "Please enter path to the message .txt file: ";
				//std::cin.ignore();
				//std::getline(std::cin, userInput);

				file.open(userInput, std::ios::binary); // open in binary mode to fix shift errors?
				if (!file) { // checking if file did not open
					std::cerr << "File could not be opened";
					break;
				}

				while (std::getline(file, line)) {
					msg += line;
				}
				encryption encrypt(msg);
				file.close();
				std::cout << "\n\nRan Successfully :) \n\n";
				break;
			}
			case 2: { // (Decrypt Message)
				std::cout << "Please enter path to the message .txt file: ";
				std::cin.ignore();
				std::getline(std::cin, userInput);

				file.open(userInput, std::ios::binary); // open in binary mode to fix shift errors?
				if (!file) { // checking if file did not open
					std::cerr << "File could not be opened";
					break;
				}

				while (std::getline(file, line)) {
					msg += line;
				}
				decryption decrypt(msg);
				file.close();
				std::cout << "\n\nRan Successfully :) \n\n";
				break;
			}
			case 3: { // (Test)
				encryption enc;

				file.open("encrypted_message.txt", std::ios::binary); // open in binary mode to fix shift errors?
				if (!file) { // checking if file did not open
					std::cerr << "File could not be opened";
					break;
				}

				std::cout << "File Opened Successfully \n";

				file.clear();

				while (std::getline(file, line)) {
					msg += line;
					std::cout << "are we stuck?\n";
					std::cout << "EOF: " << file.eof() << ", Fail: " << file.fail() << "\n";
				}
				file.close();
				std::cout << "loop ended file closed\n";
				decryption decrypt(msg);
				std::cout << "\n\nRan Successfully :) \n\n";
				break;
			}
			case 4: // (Exit)
				break;
			case 5: { // do n sizes match (default constructor)
				encryption enc;
				std::cout << "Encryption n: " << enc.getN();
				while (std::getline(file, line)) {
					msg += line;
					std::cout << "are we stuck?\n";
					std::cout << "EOF: " << file.eof() << ", Fail: " << file.fail() << "\n";
				}
				decryption dec(msg);
				std::cout << "Decryption n: " << dec.getN() << std::endl;
				break;
			}
			default:
				std::cout << "Invalid menu option \n";
				std::cout << "Please select another option from the menu: ";
				std::cin.ignore();
				std::cin >> userChoice;
		}
			std::cout << "Please select another option from the menu: ";
			//std::cin.clear();
			std::cin >> userChoice;
	}
	return 0;
}