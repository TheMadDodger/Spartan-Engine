#include "stdafx.h"
#include "GUIDTestScene.h"
#include <GUID.h>

GUIDTestScene::GUIDTestScene() : GameScene("GUID Test Scene")
{
}


GUIDTestScene::~GUIDTestScene()
{
}

void GUIDTestScene::Initialize(const GameContext & gameContext)
{
	GUID guid = Utilities::GenerateGUID();
	//Utilities::Debug::LogInfo(guid);
}

void GUIDTestScene::Update(const GameContext & gameContext)
{
}

void GUIDTestScene::Draw(const GameContext & gameContext)
{
}
