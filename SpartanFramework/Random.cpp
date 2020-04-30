#include "stdafx.h"
#include "Random.h"

namespace SpartanEngine
{
	Lehmer::Lehmer(uint32_t seed) : Random(seed)
	{
	}

	Lehmer::~Lehmer()
	{
	}

	uint32_t Lehmer::GetNext()
	{
		m_Seed += 0xe120fc15;
		uint64_t tmp;
		tmp = (uint64_t)m_Seed * 0x4a39b70d;
		uint32_t m1 = (tmp >> 32) ^ tmp;
		tmp = (uint64_t)m1 * 0x12fad5c9;
		uint32_t m2 = (tmp >> 32) ^ tmp;
		return m2;
	}

	int Math::Lehmer::GetNext(int min, int max)
	{
		return (GetNext() % (max - min)) + min;
	}

	double Math::Lehmer::GetNext(double min, double max)
	{
		return ((double)GetNext() / (double)(0x7FFFFFFF)) * (max - min) + min;
	}

	float Math::Lehmer::GetNext(float min, float max)
	{
		return ((float)GetNext() / (float)(0x7FFFFFFF)) * (max - min) + min;
	}
}