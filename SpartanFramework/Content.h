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
		const std::string& Name() const;

		template <class T>
		T* As() { return static_cast<T*>(this); };

		void SetDirty();
		bool IsDirty() const;

	protected:
		friend class ContentManager;
		friend class AssetDatabase;
		friend class AssetManager;
		friend class ScriptableObjectLoader;
		GUID m_GUID;
		bool m_IsDirty;
		std::string m_Name;
	};
}