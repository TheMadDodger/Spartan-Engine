#include "stdafx.h"
#include "StandardPropertyDrawers.h"

namespace Spartan::Editor
{
	void FloatDrawer::OnGUI(Serialization::SerializedProperty& prop) const
	{
		ImGui::InputFloat(prop.m_Name.c_str(), (float*)prop.m_MemberPointer);
	}

	void IntDrawer::OnGUI(Serialization::SerializedProperty& prop) const
	{
		ImGui::InputInt(prop.m_Name.c_str(), (int*)prop.m_MemberPointer);
	}

	void BoolDrawer::OnGUI(Serialization::SerializedProperty& prop) const
	{
		ImGui::Checkbox(prop.m_Name.c_str(), (bool*)prop.m_MemberPointer);
	}

	void DoubleDrawer::OnGUI(Serialization::SerializedProperty& prop) const
	{
		ImGui::InputDouble(prop.m_Name.c_str(), (double*)prop.m_MemberPointer);
	}

	void Vector2Drawer::OnGUI(Serialization::SerializedProperty& prop) const
	{
		ImGui::InputFloat2(prop.m_Name.c_str(), (float*)prop.m_MemberPointer);
	}
	void Vector3Drawer::OnGUI(Serialization::SerializedProperty& prop) const
	{
		ImGui::InputFloat3(prop.m_Name.c_str(), (float*)prop.m_MemberPointer);
	}
	void Vector4Drawer::OnGUI(Serialization::SerializedProperty& prop) const
	{
		ImGui::InputFloat4(prop.m_Name.c_str(), (float*)prop.m_MemberPointer);
	}
	void ColorDrawer::OnGUI(Serialization::SerializedProperty& prop) const
	{
		ImGui::ColorPicker4(prop.m_Name.c_str(), (float*)prop.m_MemberPointer);
	}
	void QuaternionDrawer::OnGUI(Serialization::SerializedProperty& prop) const
	{
		ImGui::InputFloat4(prop.m_Name.c_str(), (float*)prop.m_MemberPointer);
	}
}