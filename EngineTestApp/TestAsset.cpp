#include "stdafx.h"
#include "TestAsset.h"

TestAsset::TestAsset() : m_Value1(0.0f), m_Value2(0), m_Value3(0.0), m_Value4(false), m_Value5(0)
{
}

TestAsset::~TestAsset()
{
}

void TestAsset::DefineSerializedProperties(std::vector<Spartan::Serialization::SerializedProperty>& params)
{
	params.push_back(Spartan::Serialization::SerializedProperty(m_Value1, &m_Value1, "Value 1"));
	params.push_back(Spartan::Serialization::SerializedProperty(m_Value2, &m_Value2, "Value 2"));
	params.push_back(Spartan::Serialization::SerializedProperty(m_Value3, &m_Value3, "Value 3"));
	params.push_back(Spartan::Serialization::SerializedProperty(m_Value4, &m_Value4, "Value 4"));
	params.push_back(Spartan::Serialization::SerializedProperty(m_Value5, &m_Value5, "Value 5"));
	params.push_back(Spartan::Serialization::SerializedProperty(&m_TextureValueTest, "Texture Test"));
}
