#include "Header.h"

//File encryption process
void encrypt(std::string filename, std::string password)
{
	//open input file
	std::ifstream fin(filename.c_str(), std::ios::binary);
	if (!fin) {
		error("File not found.");
	}

	//create output binary file
	std::ofstream fenc((filename + ".enc").c_str(), std::ios::binary);
	if (!fenc)
	{
		error("Cannot create output file.");
	}

	char c;
	//create interator that iterates thru password string
	std::string::const_iterator pi;
	pi = password.begin();


	//using fin.eof() to check for end of file is dirty
	while (fin.read(&c, sizeof(c)))
	{
		c ^= *pi;		//xor the original character
		fenc.write(&c, sizeof(c));

		pi++;
		if (pi == password.end())
			pi = password.begin();
	}

	//Close all files
	fenc.close();
	fin.close();

	//Delete original file
	remove(filename.c_str());

	std::cout << "Encryption of " << filename << " successful.\n";
	std::cout << "Original file deleted." << "\n\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));

	for (int i = 5; i > 0; --i)
	{
		std::cout << "Exiting in " << i << "\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

//File decryption process
void decrypt(std::string filename, std::string password)
{
	//check if .enc file
	size_t encpos = filename.rfind(".enc");
	if (encpos == std::string::npos)
	{
		//not .enc
		error("Only .enc files can be decrypted!");
	}
	else
	{
		std::cout << "Decrypting " << filename << " using password " << password << "..." << "\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	//open input file
	std::ifstream fenc(filename.c_str(), std::ios::binary);
	if (!fenc)
	{
		error("File not found.");
	}

	//create output binary file
	filename.replace(encpos, 4, "");
	//remove .enc from filename

	std::ofstream fout(filename.c_str());
	if (!fout)
	{
		error("Cannot create output file");
	}

	char c;
	std::string::const_iterator pi;
	pi = password.begin();

	while (fenc.read(&c, sizeof(c)))
	{
		c ^= *pi;		//xoring twice will get the original
		fout.put(c);

		pi++;
		if (pi == password.end())
			pi = password.begin();
	}

	fenc.close();
	fout.close();

	std::cout << "Decrypted contents to file " << filename << "..." << "\n";

	remove((filename + ".enc").c_str());
	std::cout << "Encrypted file deleted." << "\n\n";

	for (int i = 5; i > 0; --i)
	{
		std::cout << "Exiting in " << i << "\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

//Error message
void error(std::string errmsg)
{
	std::cout << "Error: " << errmsg << "\n";
	exit(1);
}