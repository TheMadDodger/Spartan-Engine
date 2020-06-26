#pragma once
#include <ostream>
#include <Windows.h>
#include <any>
#include <vector>

class SerializedAsset
{
public:
	SerializedAsset(const GUID& guid) : m_GUID(guid) {}
	virtual ~SerializedAsset() {}

	virtual const std::type_info& GetClassType() = 0;

	void Serialize(std::ostream& os);

	const GUID& GetGUID();

protected:
	virtual void DefineSerializedParams(std::vector<std::any> &params) = 0;

private:
	void PrepareData();
	std::string Serialize(std::any& data);

private:
	GUID m_GUID;
	std::vector<std::any> m_SerializedData;
};

template<class T>
class Asset : public SerializedAsset
{
public:
	Asset(const GUID& guid) : SerializedAsset(guid) {}
	virtual ~Asset() {}

	virtual const std::type_info& GetClassType() override
	{
		return typeid(T);
	}

private:

};

class TestAsset : public Asset<TestAsset>
{
public:
	TestAsset(const GUID& guid) : Asset(guid) {}
	virtual ~TestAsset() {}

	void Deserialize(std::istream& is);

private:
	void DefineSerializedParams(std::vector<std::any>& params) override;

private:
	float m_TestData1;
	bool m_TestData2;
	int m_TestData3;
	char m_TestData4;
};