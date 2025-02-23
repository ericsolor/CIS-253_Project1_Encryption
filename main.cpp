#include <iostream>
#include "encryption.hpp"
#include "decryption.hpp"

int main() {
	int userChoice = 0;
	std::string userInput;
	std::string line;
	std::ifstream file;
	std::cout << "Eric Solorzano's Encryption Project \nPlease select a menu option below: \n\n";
	std::cout << "Menu: \n1.) Encrypt Message \n2.) Decrypt Message \n3.) Demonstration \n4.) Exit\n";

	try { // try catch statement to ensure user input is valid
		std::cout << "Menu Choice: ";
		if (!(std::cin >> userChoice)) {
			throw std::invalid_argument("Invalid input! Please enter a number.");
		}
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		std::cin.clear();
		std::cin.ignore();
		userChoice = -1;
	}

	while (userChoice != 4) {
			switch (userChoice) {
			case 1: { // (Encrypt message)
				std::string msg;
				msg.clear();
				std::cout << "Please enter path to the message .txt file: ";

				try { // try catch statement to ensure that user input is valid
					std::cin.clear();
					std::cin.ignore();
					std::getline(std::cin, userInput);
				}
				catch (const std::invalid_argument& e) {
					std::cerr << "Error: " << e.what() << std::endl;
					std::cin.clear();
					std::cin.ignore();
					break;
				}

				file.open(userInput, std::ios::binary); // opening the file in binary to bit corruption
				if (!file) { // checking if file did not open
					std::cerr << "File could not be opened\n";
					break;
				}

				while (std::getline(file, line)) { // appending each line in file to msg
					msg += line;
				}
				encryption encrypt(msg); // encrypting message
				file.close();
				std::cout << "\n\nRan Successfully \n\n";
				break;
			}
			case 2: { // (Decrypt Message)
				std::string msg;
				std::cout << "Please enter path to the message .txt file: ";

				try { // try catch statement to ensure that user input is valid
					std::cin.clear();
					std::cin.ignore();
					std::getline(std::cin, userInput);
				}
				catch (const std::invalid_argument& e) {
					std::cerr << "Error: " << e.what() << std::endl;
					std::cin.clear();
					std::cin.ignore();
					break;
				}

				file.open(userInput, std::ios::binary); // opening the file in binary to bit corruption
				if (!file) { // checking if file did not open
					std::cerr << "File could not be opened \n";
					break;
				}

				while (std::getline(file, line)) { // appending each line in file to msg
					msg += line;
				}
				decryption decrypt(msg); // decrypting message
				file.close();
				std::cout << "\n\nRan Successfully \n\n";
				break;
			}
			case 3: { // (Demonstration)
				std::string msg;
				encryption enc; // calling default constructor for encryption

				file.open("encrypted_message.txt", std::ios::binary); // opening the file in binary to bit corruption
				if (!file) { // checking if file did not open
					std::cerr << "File could not be opened\n";
					break;
				}

				while (std::getline(file, line)) { // appending each line in file to msg
					msg += line;
				}
				file.close();
				decryption dec(msg, enc.getDemoMode()); // activating demo mode in decryption
				std::cout << "Ran Sucessfully \n\n";
				break;
			}
			case 4: // (Exit)
				break;
			default: // Invalid user input
				std::cout << "\nInvalid menu option \n";
		}

			try { // try catch statement to ensure that user input is valid
				std::cout << "Please select another option from the menu: \n\n";
				std::cout << "Menu: \n1.) Encrypt Message \n2.) Decrypt Message \n3.) Demonstration \n4.) Exit\n";
				std::cout << "Menu Choice: ";
				std::cin >> userChoice;
			}
			catch (const std::invalid_argument& e) {
				std::cerr << "Error: " << e.what() << std::endl;
				std::cin.clear();
				std::cin.ignore();
				userChoice = -1;
			}
	}
	return 0;
}