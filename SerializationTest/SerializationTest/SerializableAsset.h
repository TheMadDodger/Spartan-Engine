#pragma once
#include <ostream>
#include <Windows.h>
#include <any>
#include <vector>

struct SerializedParam
{
public:
	std::any m_Serialized;
	void* m_MemberPointer;
};

class SerializedAsset
{
public:
	SerializedAsset(const GUID& guid);
	virtual ~SerializedAsset() {}

	virtual const std::type_info& GetClassType() = 0;

	void Serialize(std::ofstream& os);
	void Deserialize(std::ifstream& os);

	const GUID& GetGUID();

protected:
	virtual void DefineSerializedParams(std::vector<SerializedParam> &params) = 0;
	virtual SerializedAsset* Create(const GUID& guid) = 0;

private:
	void PrepareData();
	void Serialize(SerializedParam& data, std::ofstream& fileStream);
	void Deserialize(SerializedParam& data, std::ifstream& fileStream);

private:
	friend class AssetFactory;
	const GUID m_GUID;
	std::vector<SerializedParam> m_SerializedData;
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
	virtual SerializedAsset* Create(const GUID& guid) override
	{
		return new T(guid);
	}
};

class TestAsset : public Asset<TestAsset>
{
public:
	TestAsset(const GUID& guid) : Asset(guid), m_TestData1(500.0f), m_TestData2(true), m_TestData3(25), m_TestData4('X') {}
	virtual ~TestAsset() {}

private:
	void DefineSerializedParams(std::vector<SerializedParam>& params) override;

public:
	float m_TestData1;
	bool m_TestData2;
	int m_TestData3;
	char m_TestData4;
};