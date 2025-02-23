#include <iostream>
#include "encryption.hpp"
#include "decryption.hpp"

int main() {
	int userChoice = 0;
	std::string userInput;
	std::string line;
	std::ifstream file;
	std::cout << "Eric Solorzano's Encryption Project \nPlease select a menu option below: \n";

	std::cout << "Input: ";
	std::cin >> userChoice;

	while (userChoice != 4) {
			switch (userChoice) {
			case 1: { // (Encrypt message)
				std::string msg;
				msg.clear();
				std::cout << "Please enter path to the message .txt file: ";
				std::cin.clear();
				std::cin.ignore();
				std::getline(std::cin, userInput);

				file.open(userInput, std::ios::binary); // open in binary mode to fix shift errors?
				if (!file) { // checking if file did not open
					std::cerr << "File could not be opened\n";
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
				std::string msg;
				std::cout << "Please enter path to the message .txt file: ";
				std::cin.clear();
				std::cin.ignore();
				std::getline(std::cin, userInput);

				file.open(userInput, std::ios::binary); // open in binary mode to fix shift errors?
				if (!file) { // checking if file did not open
					std::cerr << "File could not be opened \n";
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
			case 5: { // do n sizes match (default constructor)
				std::string msg;
				encryption enc;

				file.open("encrypted_message.txt", std::ios::binary);
				if (!file) { // checking if file did not open
					std::cerr << "File could not be opened\n";
					break;
				}

				while (std::getline(file, line)) {
					msg += line;
				}
				file.close();
				decryption dec(msg);
				std::cout << "\nRan Sucessfully\n";
				break;
			}
			default:
				std::cout << "Invalid menu option \n";
				std::cout << "Please select another option from the menu: ";
				std::cin.clear();
				std::cin.ignore();
				std::cin >> userChoice;
		}

			std::cout << "Please select another option from the menu: ";
			std::cin >> userChoice;
	}
	return 0;
}