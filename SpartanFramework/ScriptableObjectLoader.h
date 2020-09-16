#pragma once
#include "ContentLoader.h"
#include "BaseAsset.h"

namespace Spartan
{
	class ScriptableObjectLoader : public ContentLoader<Serialization::BaseAsset>
	{
	public:
		ScriptableObjectLoader();
		~ScriptableObjectLoader();

		virtual bool SaveContent(Serialization::BaseAsset* pAsset, const std::string& path) override;

	private:
		Serialization::BaseAsset* LoadContent(const std::string& file) override;
	};
}