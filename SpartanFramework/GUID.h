#pragma once
#include "stdafx.h"

namespace Utilities
{
	// Generates a new GUID
	inline GUID GenerateGUID()
	{
		GUID guid = GUID();
		//guid.Data1 = RandomRange<DWORD>(0, std::numeric_limits<DWORD>().infinity());
		//guid.Data2 = RandomRange<WORD>(0, std::numeric_limits<WORD>().infinity());
		//guid.Data3 = RandomRange<WORD>(0, numeric_limits<WORD>().infinity());
		guid.Data1 = Random<unsigned long>();
		guid.Data2 = Random<unsigned short>();
		guid.Data3 = Random<unsigned short>();

		for (size_t i = 0; i < 8; ++i)
		{
			guid.Data4[i] = RandomRange<BYTE>(0, 255);
		}
		/*guid.GuidString = "";
		guid.GuidString += ((char)(guid.Data1 << 24));
		guid.GuidString += ((char)(guid.Data1 << 16));
		guid.GuidString += ((char)(guid.Data1 << 8));
		guid.GuidString += ((char)(guid.Data1));
		guid.GuidString += '-';
		guid.GuidString += ((char)(guid.Data2 << 8));
		guid.GuidString += ((char)(guid.Data2));
		guid.GuidString += '-';
		guid.GuidString += ((char)(guid.Data3 << 8));
		guid.GuidString += ((char)(guid.Data3));
		guid.GuidString += '-';*/

		return guid;
	}
}