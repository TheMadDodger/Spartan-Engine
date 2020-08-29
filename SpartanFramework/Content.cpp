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
}
