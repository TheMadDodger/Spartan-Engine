#include "stdafx.h"
#include "SerializedScene.h"

namespace Spartan
{
	SerializedScene::SerializedScene(const std::string& file) : GameScene("Serialized Scene"), Content(file)
	{
	}

	SerializedScene::~SerializedScene()
	{
	}
}