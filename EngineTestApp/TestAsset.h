#pragma once
#include <ScriptableObject.h>
#include <AssetReference.h>

class TestAsset : public Spartan::Serialization::ScriptableObject<TestAsset>
{
public:
	TestAsset();
	virtual ~TestAsset();

	virtual void DefineSerializedProperties(std::vector<Spartan::Serialization::SerializedProperty>& params) override;

private:
	float m_Value1;
	int m_Value2;
	double m_Value3;
	bool m_Value4;
	size_t m_Value5;
	Spartan::Serialization::AssetReference<Spartan::TextureData> m_TextureValueTest;
};

