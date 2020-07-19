#pragma once
#include "MathHelpers.h"

namespace Spartan
{
	namespace Utilities
	{
		inline int CalculateShifts(int index, const std::string& key)
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

		inline char ReverseScrambleSingleChar(const std::string& key, const char& c, int index)
		{
			int s = CalculateShifts(index, key);
			auto i = static_cast<int>(c);
			i -= s;
			i = i % 256;
			return static_cast<char>(i);
		}

		inline void Decrypt(const char* inFile, std::string& text, const std::string& key)
		{
			std::cout << "Decrypting using decryption key " << key << "..." << std::endl;

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

			std::cout << "Decrypted Data: " << text << std::endl;
		}
	}
}