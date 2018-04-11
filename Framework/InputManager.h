#pragma once

enum InputType
{
	Down,
	Pressed,
	Released,
};

struct InputAction
{
public:
	InputAction(const string &actionName, InputType type, char key, int keyMod = -1) : Key(key), Type(type), KeyMod(keyMod), ActionName(actionName) {}

	char Key;
	int KeyMod;
	InputType Type;
	string ActionName;

private:
	friend class InputManager;
	bool m_bIsTriggered = false;
	bool m_bTriggeredLastFrame = false;
};

class InputManager
{
public:
	InputManager();
	~InputManager();

	void AddInputAction(const InputAction &inputAction);
	bool IsActionTriggered(const string &actionName);

private:
	friend class BaseGame;
	void KeyDown(SDL_KeyboardEvent *keyboardEvent);
	void KeyUp(SDL_KeyboardEvent *keyboardEvent);
	void Update();

private:
	vector<InputAction> m_InputActions;
};

