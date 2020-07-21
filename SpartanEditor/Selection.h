#pragma once
#include <SEObject.h>

namespace Spartan::Editor
{
	class Selection
	{
	public:
		static void SetActiveObject(SEObject* pObject);
		static SEObject* GetActiveObject();

	private:
		static vector<SEObject*> m_pSelectedObjects;

	private:
		Selection();
		virtual ~Selection();
	};
}