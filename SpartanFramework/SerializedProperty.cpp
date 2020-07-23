#include "stdafx.h"
#include "SerializedProperty.h"

namespace Spartan::Serialization
{
	SerializedProperty::SerializedProperty(std::any data, void* member, const std::string& name) : m_Name(name), m_Serialized(data), m_MemberPointer(member) {}
}