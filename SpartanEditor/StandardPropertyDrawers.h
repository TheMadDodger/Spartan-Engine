#pragma once
#include "PropertyDrawer.h"

namespace Spartan::Editor
{
	class FloatDrawer : public PropertyDrawerTemplate<float>
	{
	public:
		virtual void OnGUI(Serialization::SerializedProperty& prop) const override;
	};

	class IntDrawer : public PropertyDrawerTemplate<int>
	{
	public:
		virtual void OnGUI(Serialization::SerializedProperty& prop) const override;
	};

	class BoolDrawer : public PropertyDrawerTemplate<bool>
	{
	public:
		virtual void OnGUI(Serialization::SerializedProperty& prop) const override;
	};

	class DoubleDrawer : public PropertyDrawerTemplate<double>
	{
	public:
		virtual void OnGUI(Serialization::SerializedProperty& prop) const override;
	};

	class Vector2Drawer : public PropertyDrawerTemplate<Vector2>
	{
	public:
		virtual void OnGUI(Serialization::SerializedProperty& prop) const override;
	};

	class Vector3Drawer : public PropertyDrawerTemplate<Vector3>
	{
	public:
		virtual void OnGUI(Serialization::SerializedProperty& prop) const override;
	};

	class Vector4Drawer : public PropertyDrawerTemplate<Vector4>
	{
	public:
		virtual void OnGUI(Serialization::SerializedProperty& prop) const override;
	};

	class ColorDrawer : public PropertyDrawerTemplate<Color>
	{
	public:
		virtual void OnGUI(Serialization::SerializedProperty& prop) const override;
	};

	class QuaternionDrawer : public PropertyDrawerTemplate<Quaternion>
	{
	public:
		virtual void OnGUI(Serialization::SerializedProperty& prop) const override;
	};
}