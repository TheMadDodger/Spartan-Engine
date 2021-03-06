// TextToBinary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BinaryContainer.h"

bool Convert(const char *in, const char *out);
string GetType(string &line);
void WriteWithType(const string &type, const string &line);
string Scramble(const string &key, string &text);
string ReverseScramble(const string &key, string &text);
void Encrypt(const char *inFile, const char *outFile);
void Decrypt(const char *inFile, const char *outFile);
void ConvertFile(const string &inputFile, const string &outputFile);

string EncryptionKey = "";

int main(int argc, char *argv[])
{
	string inputFile;
	string outputFile;
#ifdef _DEBUG
	cout << argc << " arguments " << endl;
	for (int i = 0; i < argc; ++i)
	{
		cout << i << ": " << argv[i] << endl;
	}
#endif

	if (argc < 3)
	{
#ifdef _DEBUG
		inputFile = "test.txt";
		outputFile = "test.bin";
		Convert(inputFile.data(), outputFile.data());
#else
		cout << "Missing Arguments" << endl;
		cin.get();
		return -1;
#endif // _DEBUG
	}
	else// if (argc >= 4)
	{
		inputFile = argv[1];
		outputFile = argv[2];
		string arg = argv[3];

		if (arg == "-c") // Convert
		{
			ConvertFile(inputFile, outputFile);
		}
		else if (arg == "-d") // Decrypt
		{
			if (argc <= 4)
			{
				cout << "Please specify a decryption key >";
				getline(cin, EncryptionKey);
			}
			else
			{
				EncryptionKey = argv[4];
			}
			Decrypt(inputFile.data(), outputFile.data());
		}
		else if (arg == "-e") // Encrypt
		{
			if (argc <= 4)
			{
				cout << "Please specify an encryption key >";
				getline(cin, EncryptionKey);
			}
			else
			{
				EncryptionKey = argv[4];
			}
			Encrypt(inputFile.data(), outputFile.data());
		}
		else
		{
			cout << "Invalid Arguments" << endl;
			cin.get();
			return -1;
		}
	}

	cin.get();
	return 0;
}

void ConvertFile(const string &inputFile, const string &outputFile)
{
	cout << "Converting " << inputFile << " to binary file " << outputFile << endl;

	auto in = string("./") + inputFile;
	auto out = string("./") + outputFile;

	if (!Convert(inputFile.data(), outputFile.data()))
	{
		cout << "Failed!" << endl;
		return;
	}

	cout << "DONE!" << endl;

	if (EncryptionKey != "")
	{
		auto oe = outputFile + ".secure";
		Encrypt(outputFile.data(), oe.data());
	}
}

bool Convert(const char *in, const char *out)
{
	using namespace Utilities;
	if (!BinaryContainer::OpenWrite(out))
	{
		cout << "Could not create binary file " << out << endl;
		return false;
	}

	ifstream inStream;
	inStream.open(in);

	if (!inStream.is_open())
	{
		cout << "Could not open text file " << in << endl;
		return false;
	}

	while (!inStream.eof())
	{
		string line;
		getline(inStream, line);
		cout << line << endl;
		auto type = GetType(line);
		cout << "TYPE: " << type;
		cout << " VALUE: " << line << endl;

		WriteWithType(type, line);
	}

	inStream.close();
	BinaryContainer::Close();

	return true;
}

string GetType(string &line)
{
	auto type = line.substr(0, line.find(':'));
	line = line.substr(line.find(':') + 1, line.length());

	return type;
}

void WriteWithType(const string &type, const string &line)
{
	using namespace Utilities;
	if (type == "int" || type == "i")
	{
		try
		{
			auto value = std::stoi(line);
			BinaryContainer::Write<int>(value);
		}
		catch (const std::exception&)
		{
			cout << "ERROR: Could not parse " << line << " to an int";
		}
	}
	else if (type == "float" || type == "f")
	{
		try
		{
			auto value = std::stof(line);
			BinaryContainer::Write<float>(value);
		}
		catch (const std::exception&)
		{
			cout << "ERROR: Could not parse " << line << " to a float";
		}
	}
	else if (type == "double" || type == "d")
	{
		try
		{
			auto value = std::stod(line);
			BinaryContainer::Write<double>(value);
		}
		catch (const std::exception&)
		{
			cout << "ERROR: Could not parse " << line << " to a double";
		}
	}
	else if (type == "byte" || type == "b")
	{
		try
		{
			auto value = std::stoi(line);
			BinaryContainer::Write<char>(value);
		}
		catch (const std::exception&)
		{
			cout << "ERROR: Could not parse " << line << " to a char";
		}
	}
	else if (type == "string" || type == "s")
	{
		try
		{
			BinaryContainer::WriteString(line);
		}
		catch (const std::exception&)
		{
			cout << "ERROR: Could not parse " << line << " to a string";
		}
	}
	else if (type == "key" || type == "k")
	{
		try
		{
			EncryptionKey = line;
		}
		catch (const std::exception&)
		{
			cout << "ERROR: Could not parse " << line << " to an encryption key";
		}
	}
}

int CalculateShifts(int index, const string &key)
{
	int total = 0;
	for (char c : key)
	{
		int i = static_cast<int>(c);
		auto m = ((index + 1) * 123) % i;
		switch (m)
		{
		case 0:
			total += i;
			break;
		case 1:
			total -= i;
			break;
		case 2:
			if (i != 0) total /= i;
			break;
		case 3:
			if (i != 0) total *= i;
			break;
		case 4:
			if (i != 0) total = total + i / 2;
			break;
		case 5:
			if (i != 0) total = total - i / 2;
			break;
		case 6:
			total += i;
			break;
		case 7:
			total -= i;
			break;
		case 8:
			if (i != 0) total /= i;
			break;
		case 9:
			if (i != 0) total *= i;
			break;
		case 10:
			if (i != 0) total = total + i / 2;
			break;
		case 11:
			if (i != 0) total = total - i / 2;
			break;
		default:
			total += i / 20;
			break;
		}
	}

	return total;
}

string Scramble(const string &key, string &text)
{
	int index = 0;
	for (char &c : text)
	{
		int s = CalculateShifts(index, key);
		auto i = static_cast<int>(c);
		i += s;
		i = i % 256;
		char ori = c;
		c = static_cast<char>(i);
		++index;
	}
	return text;
}

string ReverseScramble(const string &key, string &text)
{
	int index = 0;
	for (char &c : text)
	{
		int s = CalculateShifts(index, key);
		auto i = static_cast<int>(c);
		i -= s;
		i = i % 256;
		char ori = c;
		c = static_cast<char>(i);
		++index;
	}
	return text;
}

void Encrypt(const char *inFile, const char *outFile)
{
	cout << "Encrypting using encryption key " << EncryptionKey << "..." << endl;

	string l;
	using namespace Utilities;
	BinaryContainer::OpenRead(inFile);
	while (!BinaryContainer::ReachedEndOfFile())
	{
		char c = BinaryContainer::Read<char>();
		l += c;
	}
	BinaryContainer::Close();

	Scramble(EncryptionKey, l);

	cout << l << endl;
	cout << endl;
	cout << "Exporting encrypted data to file " << outFile << endl;

	using namespace Utilities;
	BinaryContainer::OpenWrite(outFile);
	for (const char &c : l)
	{
		BinaryContainer::Write<char>(c);
	}
	BinaryContainer::Close();
	

	cout << "Decrypting with same key..." << endl;

	ReverseScramble(EncryptionKey, l);

	cout << l << endl;
}

void Decrypt(const char *inFile, const char *outFile)
{
	cout << "Decrypting using decryption key " << EncryptionKey << "..." << endl;

	string l;
	using namespace Utilities;
	BinaryContainer::OpenRead(inFile);
	while (!BinaryContainer::ReachedEndOfFile())
	{
		char c = BinaryContainer::Read<char>();
		l += c;
	}
	BinaryContainer::Close();

	ReverseScramble(EncryptionKey, l);

	cout << l << endl;
	cout << endl;
	cout << "Exporting decrypted data to file " << outFile << endl;

	BinaryContainer::OpenWrite(outFile);
	for (const char &c : l)
	{
		BinaryContainer::Write<char>(c);
	}
	BinaryContainer::Close();
}