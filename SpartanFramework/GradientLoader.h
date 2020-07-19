#pragma once
#include "ContentLoader.h"
#include "Gradient.h"

namespace Spartan
{
	class GradientLoader : public ContentLoader<Gradient>
	{
	public:
		GradientLoader();
		~GradientLoader();

	private:
		virtual Gradient* LoadContent(const std::string& file) override;
		Gradient* LoadBinary(const std::string& file);
		Gradient* LoadText(const std::string& file);
	};
}