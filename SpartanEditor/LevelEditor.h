#pragma once
#include <GameScene.h>

class LevelEditor : public GameScene
{
public:
	LevelEditor();
	virtual ~LevelEditor();

	void RenderGUI();

private:
	virtual void Initialize(const GameContext &gameContext);
	virtual void Update(const GameContext &gameContext);
	virtual void Draw(const GameContext &gameContext);

private:
	void CreateObjectList();
	void ChildrenList(GameObject *pChild);
	void CreateInspector();
	void ObjectMenu();

private:
	int m_I = 0;
	GameObject *m_CurrentSelectedObject = nullptr;
	GameObject *m_CurrentRightClickedObject = nullptr;

	std::map<std::string, bool> m_ComponentsCreated;
};

