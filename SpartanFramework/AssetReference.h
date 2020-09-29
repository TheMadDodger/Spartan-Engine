#pragma once
#include "Content.h"

namespace Spartan::Serialization
{
	struct BaseAssetReference
	{
	public:
		BaseAssetReference();
		virtual ~BaseAssetReference();
		virtual const std::type_info& GetAssetType() { return typeid(Content); }
		Content* GetReferencedAsset();
		void SetAsset(Content* pAsset);
		void SetAsset(const GUID& guid);
		const GUID& GetAssetGUID() const;
		bool IsDirty();

	private:
		void CollectAsset();

	private:
		GUID m_AssetGUID;
		Content* m_pReferencedAsset;
		bool m_IsDirty;
	};

	template<class T>
	struct AssetReference : public BaseAssetReference
	{
	public:
		AssetReference() {}
		virtual ~AssetReference() {}

		virtual const std::type_info& GetAssetType() override
		{
			return typeid(T);
		}

		T* GetTypedReferencedAsset()
		{
			Content* pAsset = GetReferencedAsset();
			if (pAsset == nullptr) return nullptr;
			return (T*)pAsset;
		}
	};
}
