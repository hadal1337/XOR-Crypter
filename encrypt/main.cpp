#include "Header.h"

int main()
{
	std::string filename;
	std::string password;
	std::cout << "Make sure file is in same folder as EXE\n";
	std::cout << "Enter filename (including extension): ";
	std::getline(std::cin, filename);
	std::cout << "Set new password or enter existing password: ";
	std::getline(std::cin, password);

	char uInput;
	std::cout << "Encrypt(1) or Decrypt(2)? (1/2)";
	std::cin >> uInput;

	while (uInput != '1' && uInput != '2')
	{
		std::cout << "Please enter a valid number: \n";
		std::cin >> uInput;
	}
	if (uInput == '1')
	{
		encrypt(filename, password);
	}
	else if (uInput == '2')
	{
		decrypt(filename, password);
	}
}