#include "stdafx.h"
#include "Commands.h"

namespace SpartanEngine
{
#ifdef _DEBUG
	std::vector<BaseParser*> Parser::m_Parsers = {
		new IntParser(),
		new FloatParser(),
		new StringParser(),
		new SizeTParser(),
	};
#endif // _DEBUG
}