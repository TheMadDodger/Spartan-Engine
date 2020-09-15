#pragma once
#include "Tumbnail.h"
#include "MetaData.h"

namespace Spartan::Editor
{
	class BaseTumbnailGenerator
	{
	public:
		BaseTumbnailGenerator();
		virtual ~BaseTumbnailGenerator();

		virtual TextureData* GetTumbnail(const Spartan::Serialization::MetaData& metaData) = 0;

	protected:
		virtual const std::type_info& GetAssetType() = 0;

	private:
		friend class Tumbnail;
	};

	template<class T>
	class TumbnailGenerator : public BaseTumbnailGenerator
	{
	public:
		TumbnailGenerator() {}
		virtual ~TumbnailGenerator() {}
		const std::type_info& GetAssetType() override { return typeid(T); }
		virtual TextureData* GetTumbnail(const Spartan::Serialization::MetaData& metaData) = 0;
	};
}