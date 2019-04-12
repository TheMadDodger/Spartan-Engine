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
	Utilities::GUID guid = Utilities::GUID::GenerateGUID();
	//Utilities::Debug::LogInfo(guid);
}

void GUIDTestScene::Update(const GameContext & gameContext)
{
}

void GUIDTestScene::Draw(const GameContext & gameContext)
{
}
