#include "stdafx.h"
#include "Content.h"

namespace Spartan
{
	Content::Content(const std::string& file) : m_FileName(file) {}
	Content::~Content() {}
	const std::string& Content::GetFile() { return m_FileName; }

}