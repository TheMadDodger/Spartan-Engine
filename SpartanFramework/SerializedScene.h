#pragma once
#include "GameScene.h"
#include "ContentManager.h"
#include "ISerializable.h"

namespace Spartan
{
	class SerializedScene : public GameScene, Content
	{
	public:
		SerializedScene(const std::string& file);
		virtual ~SerializedScene();
	};
}