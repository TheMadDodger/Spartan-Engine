#pragma once
#include <fstream>

namespace Spartan
{
	class ISerializable
	{
	public:
		virtual void Serialize(std::ofstream& fileStream) = 0;
		virtual void Deserialize(std::ifstream& fileStream) = 0;
	};
}