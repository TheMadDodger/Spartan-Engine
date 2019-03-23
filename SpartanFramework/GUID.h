#pragma once
#include "stdafx.h"

struct GUID
{
	// Generates a new GUID
	static GUID GenerateGUID()
	{
		// TODO: Look up a GUID algorithm

	}

private:
	GUID() {}

	DWORD Data1;
	WORD Data2;
	WORD Data2;
	BYTE Data4[8];
};

