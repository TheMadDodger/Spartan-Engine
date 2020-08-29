#include "stdafx.h"
#include "SEObject.h"

namespace Spartan
{
	//std::map<size_t, SEObject> SEObject::m_RegisteredClasses;

	SEObject* SEObject::CreateObject(const std::type_info& type)
	{
		size_t hashCode = type.hash_code();
		return CreateObject(hashCode);
	}

	SEObject* SEObject::CreateObject(size_t hashCode)
	{
		auto it = m_RegisteredClasses.find(hashCode);
		if (it == m_RegisteredClasses.end()) return nullptr;
		return m_RegisteredClasses[hashCode]->Create();
	}
}
