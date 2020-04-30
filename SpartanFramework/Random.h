#pragma once
#include "SEObject.h"
#include <cstdint>

namespace SpartanEngine
{
	namespace Math
	{
		template<typename T>
		class Random
		{
		public:
			Random(T seed) : m_Seed(seed) {};
			~Random() {};

			virtual T GetNext() = 0;
			virtual void SetSeed(T seed) { m_Seed = seed; }

		protected:
			T m_Seed;
		};

		class Lehmer : public Random<uint32_t>
		{
		public:
			Lehmer(uint32_t seed);
			~Lehmer();

			uint32_t GetNext() override;

			int GetNext(int min, int max);
			double GetNext(double min, double max);
			float GetNext(float min, float max);
		};
	}
}
