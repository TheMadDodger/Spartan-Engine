#pragma once
#include <any>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <guiddef.h>

struct BaseSerializer
{
public:
	virtual const std::type_info& GetSerializedType() = 0;
	virtual std::string Serialize(std::any& data) = 0;
};

template<typename T>
struct TypeSerializer : public BaseSerializer
{
public:
	virtual const std::type_info& GetSerializedType() override
	{
		return typeid(T);
	}

	std::string Serialize(std::any& data) override
	{
		return SerializeData(data);
	}

protected:
	// Default serializer
	virtual std::string SerializeData(std::any& data)
	{
		std::stringstream s = std::stringstream();
		s << std::any_cast<T>(data);
		return s.str();
	}
};

struct GUIDSerializer : public TypeSerializer<GUID>
{
private:
	virtual std::string SerializeData(std::any& data) override
	{
		std::stringstream s = std::stringstream();
		GUID guid = std::any_cast<GUID>(data);
		s << guid.Data1;
		s << guid.Data2;
		s << guid.Data3;
		s << guid.Data4;
		return s.str();
	}
};

class Serializer
{
public:
	static void LoadSerializers();
	static BaseSerializer* GetSerializer(const std::type_info& type);

private:
	static std::map<const std::type_info&, BaseSerializer> m_Serializers;
};
