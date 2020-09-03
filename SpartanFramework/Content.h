#pragma once
#include "SEObject.h"

namespace Spartan
{
	class Content : public SEObject // Base Class for content
	{
	public:
		Content();
		virtual ~Content();
		const GUID& GetGUID() const;

		template <class T>
		T* As() { return static_cast<T*>(this); };

	protected:
		friend class ContentManager;
		friend class AssetDatabase;
		GUID m_GUID;
	};
}