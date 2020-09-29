#include "stdafx.h"
#include "Content.h"

namespace Spartan
{
	Content::Content() {}

	Content::~Content() {}

	const GUID& Content::GetGUID() const
	{
		return m_GUID;
	}

	const std::string& Content::Name() const
	{
		return m_Name;
	}

	void Content::SetDirty()
	{
		m_IsDirty = true;
	}

	bool Content::IsDirty() const
	{
		return m_IsDirty;
	}
}
