// TreeReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BinaryContainer.h"

void Read(const char *inFile, const string &decryptKey);

int main()
{
	string file, key;
	cout << "Filename to read: ";
	getline(cin, file);
	
	using namespace Utilities;
	/*BinaryContainer::OpenRead(file.data());
	cout << BinaryContainer::Read<char>() << endl;
	cout << BinaryContainer::Read<int>() << endl;
	cout << BinaryContainer::ReadString() << endl;
	cout << BinaryContainer::ReadString() << endl;
	cout << BinaryContainer::Read<float>() << endl;

	cout << BinaryContainer::Read<int>() << endl;
	cout << BinaryContainer::ReadString() << endl;
	cout << BinaryContainer::ReadString() << endl;
	cout << BinaryContainer::Read<float>() << endl;

	cout << BinaryContainer::Read<int>() << endl;
	cout << BinaryContainer::ReadString() << endl;
	cout << BinaryContainer::ReadString() << endl;
	cout << BinaryContainer::Read<float>() << endl;

	cout << BinaryContainer::Read<int>() << endl;
	cout << BinaryContainer::ReadString() << endl;
	cout << BinaryContainer::ReadString() << endl;
	cout << BinaryContainer::Read<float>() << endl;

	cout << BinaryContainer::Read<int>() << endl;
	cout << BinaryContainer::ReadString() << endl;
	cout << BinaryContainer::ReadString() << endl;
	cout << BinaryContainer::Read<float>() << endl;

	cout << BinaryContainer::Read<int>() << endl;
	cout << BinaryContainer::ReadString() << endl;
	cout << BinaryContainer::ReadString() << endl;
	cout << BinaryContainer::Read<float>() << endl;

	cout << BinaryContainer::Read<char>() << endl;
	BinaryContainer::Close();*/

	//cin.get();

	cout << "Decryption key >";
	getline(cin, key);



	Read(file.data(), key);

	cin.get();

    return 0;
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

char ReverseScrambleSingleChar(const string &key, const char &c, int index)
{
	int s = CalculateShifts(index, key);
	auto i = static_cast<int>(c);
	i -= s;
	i = i % 256;
	return static_cast<char>(i);
}

void Decrypt(const char *inFile, string &text, const string &key)
{
	cout << "Decrypting using decryption key " << key << "..." << endl;

	using namespace Utilities;
	int index = 0;
	BinaryContainer::OpenRead(inFile);
	while (!BinaryContainer::ReachedEndOfFile())
	{
		char c = BinaryContainer::Read<char>();
		char uc = ReverseScrambleSingleChar(key, c, index);
		text += uc;
		++index;
	}
	BinaryContainer::Close();

	cout << "Decrypted Data: " << text << endl;
}

void Read(const char *inFile, const string &decryptKey)
{
	cout << "Decrypting using decryption key " << decryptKey << "..." << endl;

	string l;
	Decrypt(inFile, l, decryptKey);

	const char *decrypteBuffer = l.data();

	using namespace Utilities;

	cout << BinaryContainer::Read<char>(decrypteBuffer) << endl;
	cout << BinaryContainer::Read<int>(decrypteBuffer) << endl;
	cout << BinaryContainer::ReadString(decrypteBuffer) << endl;
	cout << BinaryContainer::ReadString(decrypteBuffer) << endl;
	cout << BinaryContainer::Read<float>(decrypteBuffer) << endl;

	cout << BinaryContainer::Read<int>(decrypteBuffer) << endl;
	cout << BinaryContainer::ReadString(decrypteBuffer) << endl;
	cout << BinaryContainer::ReadString(decrypteBuffer) << endl;
	cout << BinaryContainer::Read<float>(decrypteBuffer) << endl;

	cout << BinaryContainer::Read<int>(decrypteBuffer) << endl;
	cout << BinaryContainer::ReadString(decrypteBuffer) << endl;
	cout << BinaryContainer::ReadString(decrypteBuffer) << endl;
	cout << BinaryContainer::Read<float>(decrypteBuffer) << endl;

	cout << BinaryContainer::Read<int>(decrypteBuffer) << endl;
	cout << BinaryContainer::ReadString(decrypteBuffer) << endl;
	cout << BinaryContainer::ReadString(decrypteBuffer) << endl;
	cout << BinaryContainer::Read<float>(decrypteBuffer) << endl;

	cout << BinaryContainer::Read<int>(decrypteBuffer) << endl;
	cout << BinaryContainer::ReadString(decrypteBuffer) << endl;
	cout << BinaryContainer::ReadString(decrypteBuffer) << endl;
	cout << BinaryContainer::Read<float>(decrypteBuffer) << endl;

	cout << BinaryContainer::Read<int>(decrypteBuffer) << endl;
	cout << BinaryContainer::ReadString(decrypteBuffer) << endl;
	cout << BinaryContainer::ReadString(decrypteBuffer) << endl;
	cout << BinaryContainer::Read<float>(decrypteBuffer) << endl;

	cout << BinaryContainer::Read<char>(decrypteBuffer) << endl;
}