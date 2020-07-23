#pragma once

namespace Spartan::Serialization
{
	struct SerializedProperty
	{
	public:
		SerializedProperty(std::any data, void* member, const std::string& name);

		std::any m_Serialized;
		void* m_MemberPointer;
		const std::string m_Name;
	};
}