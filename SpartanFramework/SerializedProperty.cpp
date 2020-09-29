#include "stdafx.h"
#include "SerializedProperty.h"

namespace Spartan::Serialization
{
	SerializedProperty::SerializedProperty(std::any data, void* member, const std::string& name) :
		m_Name(name), m_Serialized(data), m_MemberPointer(member), m_pAssetReference(nullptr), m_IsContainer(false) {}

	SerializedProperty::SerializedProperty(BaseAssetReference* pAssetReference, const std::string& name) :
		m_Name(name), m_Serialized(pAssetReference), m_MemberPointer(pAssetReference), m_pAssetReference(pAssetReference), m_IsContainer(false){}
}