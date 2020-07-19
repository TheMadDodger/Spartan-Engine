#pragma once
#include "SEObject.h"

namespace Spartan
{
	class Content : SEObject // Base Class for content
	{
	public:
		Content(const std::string& file);
		virtual ~Content();
		const std::string& GetFile();

		template <class T>
		T* As() { return static_cast<T*>(this); };

	protected:
		friend class ContentManager;
		const std::string m_FileName;
	};
}