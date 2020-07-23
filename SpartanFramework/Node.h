#pragma once
#include "SEObject.h"

namespace Spartan
{
	class Node : SEObject
	{
	public:
		Node() {}
		~Node() {}

		virtual const std::type_info& GetBaseType() override { return typeid(Node); }
		virtual const std::type_info& GetType() override { return typeid(Node); }

	private:

	};
}