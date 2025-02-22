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

	while (userChoice != 4) {
			switch (userChoice) {
			case 1: { // (Encrypt message)
				std::cout << "Please enter path to the message .txt file: ";
				std::getline(std::cin, userInput);
				file.open(userInput);

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
				std::getline(std::cin, userInput);
				file.open(userInput);

				while (std::getline(file, line)) {
					msg += line;
				}
				decryption decrypt(msg);
				file.close();
				std::cout << "\n\nRan Successfully :) \n\n";
				break;
			}
			case 3: { // (Test)
				encryption enc();
				file.open("encrypted_message.txt");
				while (std::getline(file, line)) {
					msg += line;
				}
				file.close();
				decryption decrypt(msg);
				std::cout << "\n\nRan Successfully :) \n\n";
				break;
			}
			case 4: // (Exit)
				break;
			default:
			std::cout << "Invalid menu option \n";
			std::cout << "Please select another option from the menu: ";
			std::cin >> userChoice;
		}
	}
	return 0;
}