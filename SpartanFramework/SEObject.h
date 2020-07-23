#pragma once
namespace Spartan
{
	class SEObject
	{
	public:
		SEObject() {}
		virtual ~SEObject() {}

		virtual const std::type_info& GetBaseType() = 0;
		virtual const std::type_info& GetType() = 0;

	private:

	};
}