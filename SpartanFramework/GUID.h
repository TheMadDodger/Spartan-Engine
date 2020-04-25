#pragma once
#include "stdafx.h"

namespace SpartanEngine
{
	namespace Utilities
	{
		// Generates a new GUID
		inline GUID GenerateGUID()
		{
			GUID guid = GUID();
			guid.Data1 = Random<unsigned long>();
			guid.Data2 = Random<unsigned short>();
			guid.Data3 = Random<unsigned short>();

			for (size_t i = 0; i < 8; ++i)
			{
				guid.Data4[i] = RandomRange<BYTE>(0, 255);
			}

			return guid;
		}

		inline std::string ConvertToHex(unsigned char c)
		{
			unsigned char partOne = c >> 4;
			unsigned char partTwo = c << 4;
			partTwo = partTwo >> 4;

			if (partOne < 10)
			{
				partOne = to_string(partOne)[0];
			}
			else
			{
				switch (partOne)
				{
				case 10:
					partOne = 'A';
					break;
				case 11:
					partOne = 'B';
					break;
				case 12:
					partOne = 'C';
					break;
				case 13:
					partOne = 'D';
					break;
				case 14:
					partOne = 'E';
					break;
				case 15:
					partOne = 'F';
					break;
				default:
					break;
				}
			}

			if (partTwo < 10)
			{
				partTwo = to_string(partTwo)[0];
			}
			else
			{
				switch (partTwo)
				{
				case 10:
					partTwo = 'A';
					break;
				case 11:
					partTwo = 'B';
					break;
				case 12:
					partTwo = 'C';
					break;
				case 13:
					partTwo = 'D';
					break;
				case 14:
					partTwo = 'E';
					break;
				case 15:
					partTwo = 'F';
					break;
				default:
					break;
				}
			}

			string s = "";
			s += partOne;
			s += partTwo;
			return s;
		}

		inline string GUIDToString(const GUID& guid)
		{
			std::string guidString = "";
			guidString += ConvertToHex((unsigned char)(guid.Data1 >> 24));
			guidString += ConvertToHex((unsigned char)(guid.Data1 >> 16));
			guidString += ConvertToHex((unsigned char)(guid.Data1 >> 8));
			guidString += ConvertToHex((unsigned char)(guid.Data1));
			guidString += '-';
			guidString += ConvertToHex((unsigned char)(guid.Data2 >> 8));
			guidString += ConvertToHex((unsigned char)(guid.Data2));
			guidString += '-';
			guidString += ConvertToHex((unsigned char)(guid.Data3 >> 8));
			guidString += ConvertToHex((unsigned char)(guid.Data3));
			guidString += '-';

			for (size_t i = 0; i < 8; ++i)
			{
				if (i == 2) guidString += '-';
				guidString += ConvertToHex(guid.Data4[i]);
			}
			return guidString;
		}
	}
}