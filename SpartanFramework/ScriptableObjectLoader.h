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

	private:
		Serialization::BaseAsset* LoadContent(const std::string& file) override;
	};
}