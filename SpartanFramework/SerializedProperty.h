#pragma once
#include "AssetReference.h"

namespace Spartan::Serialization
{
	struct SerializedProperty
	{
	public:
		SerializedProperty(std::any data, void* member, const std::string& name);
		SerializedProperty(BaseAssetReference* pAssetReference, const std::string& name);

		//virtual void SetData(int index, std::any data) {}

		virtual void Resize(size_t newSize) {}
		virtual void LoadContainer() {}

		std::any m_Serialized;
		void* m_MemberPointer;
		const std::string m_Name;
		BaseAssetReference* m_pAssetReference;
		bool m_IsContainer;

		std::vector<SerializedProperty> m_ArrayProperties;
	};

	template<typename T>
	struct SerializedContainer : public SerializedProperty
	{
	public:
		SerializedContainer(std::vector<T>* pContainer, const std::string& name) : m_pContainer(pContainer), SerializedProperty(pContainer, pContainer, name)
		{
			m_IsContainer = true;
		}

	private:
		virtual void Resize(size_t newSize) override
		{
			size_t lastSize = m_pContainer->size();
			m_pContainer->resize(newSize);
		}

		virtual void LoadContainer() override
		{
			m_ArrayProperties.resize(m_pContainer->size());

		}

		std::vector<T>* m_pContainer;
	};
}