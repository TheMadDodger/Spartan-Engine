#include "stdafx.h"
#include "PropertyDrawer.h"

namespace Spartan::Editor
{
	vector<PropertyDrawer*> PropertyDrawer::m_PropertyDrawers = vector<PropertyDrawer*>();

	PropertyDrawer::PropertyDrawer()
	{
	}

	PropertyDrawer::~PropertyDrawer()
	{
	}

	bool PropertyDrawer::OnGUI(Serialization::SerializedProperty& prop) const
	{
		ImGui::Text(prop.m_Name.c_str());
	}

	bool PropertyDrawer::DrawProperty(Serialization::SerializedProperty& prop)
	{
		auto it = std::find_if(m_PropertyDrawers.begin(), m_PropertyDrawers.end(), [&](PropertyDrawer* propertyDrawer)
			{
				return propertyDrawer->GetPropertyType() == prop.m_Serialized.type();
			});

		if (it == m_PropertyDrawers.end())
		{
			//ImGui::Text(prop.m_Name.c_str());
			return;
		}

		PropertyDrawer* drawer = *it;
		return drawer->OnGUI(prop);
	}

	const std::type_info& PropertyDrawer::GetPropertyType() const
	{
		return typeid(PropertyDrawer);
	}

	void PropertyDrawer::Cleanup()
	{
		std::for_each(m_PropertyDrawers.begin(), m_PropertyDrawers.end(), [&](PropertyDrawer* propertyDrawer)
			{
				delete propertyDrawer;
			});
		m_PropertyDrawers.clear();
	}
}
