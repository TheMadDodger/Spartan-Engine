#pragma once

namespace Spartan::Serialization
{
	struct MetaData
	{
		MetaData(size_t hashCode, const GUID& guid, const std::string& path);

		void Write();
		static MetaData Read(const std::string& path);

		const size_t m_HashCode;
		const GUID m_GUID;
		const std::string m_Path;
	};
}