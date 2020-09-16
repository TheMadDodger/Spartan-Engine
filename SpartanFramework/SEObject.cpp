#include "stdafx.h"
#include "SEObject.h"
#include "AssetManager.h"

namespace Spartan
{
	std::map<size_t, SEObject*> SEObject::m_RegisteredClasses;
	std::vector<SEObject*> SEObject::m_AllRegisteredClasses;
	std::map<size_t, std::vector<SEObject*>> SEObject::m_RegisteredClassesPerBaseType;
	std::hash<std::string> SEObject::m_ClassHasher;

	void SEObject::DestroyClassTemplates()
	{
		std::for_each(m_AllRegisteredClasses.begin(), m_AllRegisteredClasses.end(), [](SEObject* pObject) {delete pObject; });
		m_AllRegisteredClasses.clear();
		m_RegisteredClasses.clear();
		m_RegisteredClassesPerBaseType.clear();
	}

	SEObject* SEObject::CreateObject(const std::type_info& type)
	{
		size_t hashCode = GetClassHash(type);
		return CreateObject(hashCode);
	}

	SEObject* SEObject::CreateObject(size_t hashCode)
	{
		auto it = m_RegisteredClasses.find(hashCode);
		if (it == m_RegisteredClasses.end()) return nullptr;
		return m_RegisteredClasses[hashCode]->Create();
	}

	size_t SEObject::GetClassHash(const std::type_info& type)
	{
		std::string name = type.name();
		return m_ClassHasher(name);
	}

	bool SEObject::GetRegisteredClassCount(const std::type_info& baseType, size_t& count)
	{
		size_t hashCode = GetClassHash(baseType);
		return GetRegisteredClassCount(hashCode, count);
	}

	bool SEObject::GetRegisteredClassCount(size_t baseHashCode, size_t& count)
	{
		auto it = m_RegisteredClassesPerBaseType.find(baseHashCode);
		if (it == m_RegisteredClassesPerBaseType.end()) return false;
		count = m_RegisteredClassesPerBaseType[baseHashCode].size();
		return true;
	}

	size_t SEObject::GetRegisteredClassCount()
	{
		return m_AllRegisteredClasses.size();
	}

	SEObject* SEObject::GetRegisteredClassAtIndex(const std::type_info& baseType, size_t index)
	{
		size_t hashCode = GetClassHash(baseType);
		return GetRegisteredClassAtIndex(hashCode, index);
	}

	SEObject* SEObject::GetRegisteredClassAtIndex(size_t baseHashCode, size_t index)
	{
		return m_RegisteredClassesPerBaseType[baseHashCode][index];
	}

	SEObject* SEObject::GetRegisteredClassAtIndex(size_t index)
	{
		return m_AllRegisteredClasses[index];
	}
}
