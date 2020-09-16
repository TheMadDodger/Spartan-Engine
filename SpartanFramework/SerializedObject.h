#pragma once
#include "Content.h"
#include "SerializedProperty.h"

#define PROPERTY(x) Spartan::Serialization::SerializedProperty(x, &x, #x)

namespace Spartan::Serialization
{
	class SerializedObject : public Content
	{
	public:
		SerializedObject();
		virtual ~SerializedObject();

		void CollectProperties();

		void SetDirty();
		bool IsDirty();

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
		bool m_IsDirty;
	};
}