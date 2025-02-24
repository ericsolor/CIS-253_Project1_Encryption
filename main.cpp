#include <iostream>
#include "encryption.hpp"
#include "decryption.hpp"
#include <limits>
#include <regex>

int main() {
	// Declaring Variables
	std::regex txtCheck(R"(^.*\.txt$)"); // using regular expressions to check for valid user input for .txt file
										  // defining the pattern as raw string to avoid having to double escape the '.'
	std::regex menuCheck("^[1-4]$"); // regex for menu option
	std::string userInput, userChoice;
	std::string line;
	std::ifstream file;

	std::cout << "Eric Solorzano's Encryption Project \nPlease select a menu option below:";

	while (true) {
		int menuChoice = 0;

		try { // try catch statement to ensure that user input is valid
			std::cout << "\n\nMenu: \n1.) Encrypt Message \n2.) Decrypt Message \n3.) Demonstration \n4.) Exit\n";
			std::cout << "Menu Choice: ";
			std::cin >> userChoice;
			std::cout << "\n";

			if (!std::regex_match(userChoice, menuCheck)) { // Checking if the input is an integer 1 - 4
				throw std::invalid_argument("Invalid input, please enter a number between 1 and 4");
			}

			menuChoice = std::stoi(userChoice);

		}
		catch (const std::invalid_argument& e) { // Invalid input
			std::cout << "Error: " << e.what();
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear entire input buffer until a newline character is reached
			continue;
		}

			switch (menuChoice) {
			case 1: { // (Encrypt message)

				// declaring variables
				std::string msg;
				msg.clear();

				std::cout << "Please enter path to the message .txt file: ";

				try { // try catch statement to ensure that user input is valid
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear entire input buffer until a newline character is reached
					std::getline(std::cin, userInput);
					if (!std::regex_match(userInput, txtCheck)) { // checking if the file ends with .txt using regular expression
						throw std::invalid_argument("Invalid file, must be a .txt file");
					}
				}
				catch (const std::invalid_argument& e) { // invalid input
					std::cout << "Error: " << e.what();
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear entire input buffer until a newline character is reached
					}
					break;
				}

				try { // try catch to see if file opens correctly
					file.open(userInput, std::ios::binary); // opening the file in binary to bit corruption
					if (!file) { // checking if file did not open
						throw std::runtime_error("File could not be opened, check permissions or path to file");
					}
				}
				catch (const std::runtime_error& e) { // file did not open correctly
					std::cout << "Error: " << e.what();
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
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear entire input buffer until a newline character is reached
					std::getline(std::cin, userInput);
					if (!std::regex_match(userInput, txtCheck)) { // checking if the file ends with .txt using regular expression
						throw std::invalid_argument("Invalid file, must be a .txt file");
					}
				}
				catch (const std::invalid_argument& e) { // invalid input
					std::cout << "Error: " << e.what();
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear entire input buffer until a newline character is reached
					}
					break;
				}

				try { // try catch to ensure file opens properly
					file.open(userInput, std::ios::binary); // opening the file in binary to bit corruption
					if (!file) { // checking if file did not open
						throw std::runtime_error("File could not be opened, check permissions or path to file");
					}
					if (file.peek() == std::ifstream::traits_type::eof()) { // checking if file is empty
						throw std::runtime_error("File is empty, cannot decrypt an empty file");
					}
				}
				catch (const std::runtime_error& e) { // file did not open properly
					std::cout << "Error: " << e.what();
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

				try { // try catch to ensure file opens properly
					file.open("encrypted_message.txt", std::ios::binary); // opening the file in binary to bit corruption
					if (!file) { // checking if file did not open
						throw std::runtime_error("File could not be opened, check permissions or path to file");
					}
				}
				catch (const std::runtime_error& e) { // file did not open properly
					std::cout << "Error: " << e.what();
					break;
				}

				while (std::getline(file, line)) { // appending each line in file to msg
					msg += line;
				}
				file.close();
				decryption dec(msg, enc.getDemoMode()); // activating demo mode in decryption
				std::cout << "\n\nRan Sucessfully \n\n";
				break;
			}
			case 4: // (Exit)
				return false;
			default: // Invalid user input
				std::cout << "\nSomething went really wrong here \n\n";
		}
	}
	return 0;
}