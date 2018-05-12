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
	InputAction(const string &actionName, InputType type, char key, Uint8 mouseButton = 0, SDL_Scancode keyMod = SDL_Scancode(SDL_NUM_SCANCODES + 1)) : Key(key), Type(type), KeyMod(keyMod), ActionName(actionName), MouseButton(mouseButton) {}

	char Key;
	SDL_Scancode KeyMod;
	InputType Type;
	string ActionName;
	Uint8 MouseButton;

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

	const Vector2 &GetMouseScreenPosition() { return m_MousePosition; };
	// This returns the mouse position relative to the world
	// It needs a camera matrix to transform the mouse coordiantes
	const Vector2 GetMouseWorldPosition(Matrix3X3 &cameraMatrix);
	const Vector2 &GetMouseWheelMovement() { return m_LastFrameWheelData; }

private:
	friend class BaseGame;
	void KeyDown(SDL_KeyboardEvent *keyboardEvent);
	void KeyUp(SDL_KeyboardEvent *keyboardEvent);
	void MouseUp(SDL_MouseButtonEvent *mouseButtonEvent);
	void MouseDown(SDL_MouseButtonEvent *mouseButtonEvent);
	void HandleMouseMotionEvent(SDL_MouseMotionEvent *mouseMotionEvent, int windowHieght);
	void HandleMouseScrollEvent(SDL_MouseWheelEvent *mouseWheelEvent);
	void Update();

private:
	vector<InputAction> m_InputActions;
	Vector2 m_MousePosition;
	Vector2 m_LastFrameWheelData;
};

