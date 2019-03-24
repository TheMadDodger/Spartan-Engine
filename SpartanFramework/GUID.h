#pragma once
#include "stdafx.h"

struct GUID
{
	// Generates a new GUID
	static GUID GenerateGUID()
	{
		GUID guid = GUID();
		guid.Data1 = RandomRange<DWORD>(0, numeric_limits<DWORD>().max);
		guid.Data2 = RandomRange<WORD>(0, numeric_limits<WORD>().max);
		guid.Data3 = RandomRange<WORD>(0, numeric_limits<WORD>().max);

		for (size_t i = 0; i < 8; ++i)
		{
			guid.Data4[i] = RandomRange<BYTE>(0, numeric_limits<BYTE>().max);
		}

		return guid;
	}

	bool operator==(const GUID &other)
	{
		if (other.Data1 != Data1) return false;
		if (other.Data2 != Data2) return false;
		if (other.Data3 != Data3) return false;
		
		for (size_t i = 0; i < 8; ++i)
		{
			if (other.Data4[i] != Data4[i]) return false;
		}
	}

private:
	GUID() {}

	DWORD Data1;
	WORD Data2;
	WORD Data3;
	BYTE Data4[8];
};

