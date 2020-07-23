#pragma once
#include "SEObject.h"
#include "SerializedProperty.h"

namespace Spartan::Serialization
{
	class SerializedObject : public SEObject
	{
	public:
		SerializedObject();
		virtual ~SerializedObject();

		void CollectProperties();

	public:
		void Serialize(std::ofstream& os);
		void Deserialize(std::ifstream& os, int skipCount = 1);

		SerializedProperty& GetSerializedProperty(int index);
		size_t GetSerializedPropertyCount() const;

	protected:
		virtual void DefineSerializedProperties(std::vector<SerializedProperty>& params) = 0;
		void PrepareData();
		virtual void PrepareData(std::vector<SerializedProperty>&) {};

	private:
		void Serialize(SerializedProperty& data, std::ofstream& fileStream);
		void Deserialize(SerializedProperty& data, std::ifstream& fileStream);

	private:
		std::vector<SerializedProperty> m_SerializedData;
	};
}