#pragma once
#include "Manager.h"

#define INPUT_DEADZONE 3500
#define MAX_STICK_MAGNITUDE 32767

namespace SpartanEngine
{
	enum InputType
	{
		Down,
		Pressed,
		Released,
	};

	struct InputAction
	{
	public:
		InputAction(const string& actionName, InputType type, char key, Uint8 mouseButton = 0, SDL_Scancode keyMod = SDL_Scancode(SDL_NUM_SCANCODES + 1)) : Key(key), Type(type), KeyMod(keyMod), ActionName(actionName), MouseButton(mouseButton) {}

		char Key;
		SDL_Scancode KeyMod;
		InputType Type;
		string ActionName;
		Uint8 MouseButton;
		DWORD ControllerID = 0;
		WORD ControllerButton = 0;

	private:
		friend class InputManager;
		bool m_bIsTriggered = false;
		bool m_bTriggeredLastFrame = false;
	};

	enum class JoystickType
	{
		LeftThumbStick,
		RightThumbStick,
		Trigger,
	};

	class InputManager : Manager
	{
	public:
		InputManager();
		~InputManager();

		InputAction& AddInputAction(const InputAction& inputAction);
		bool IsActionTriggered(const string& actionName);
		void ReplaceInputAction(const string& actionName, const InputAction& inputAction);

		const Vector2& GetMouseScreenPosition() { return m_MousePosition; };
		// This returns the mouse position relative to the world
		// It needs a camera matrix to transform the mouse coordiantes
		const Vector3 GetMouseWorldPosition(Matrix4X4& cameraMatrix);
		const Vector2& GetMouseWheelMovement() { return m_LastFrameWheelData; }

		Vector2 GetControllerJoystickPosition(DWORD controllerID, const JoystickType& stick);
		bool IsControllerConnected(DWORD controllerID);

		bool IsMouseButtonDown(uint8 button);

	private:
		friend class GameTool;
		friend class BaseGame;
		void KeyDown(SDL_KeyboardEvent* keyboardEvent);
		void KeyUp(SDL_KeyboardEvent* keyboardEvent);
		void MouseUp(SDL_MouseButtonEvent* mouseButtonEvent);
		void MouseDown(SDL_MouseButtonEvent* mouseButtonEvent);
		void HandleMouseMotionEvent(SDL_MouseMotionEvent* mouseMotionEvent, int windowHieght);
		void HandleMouseScrollEvent(SDL_MouseWheelEvent* mouseWheelEvent);
		void Update();
		void ControllerUpdate();

	private:
		vector<InputAction> m_InputActions;
		Vector2 m_MousePosition;
		Vector2 m_LastFrameWheelData;

		uint8 m_MouseButton = 0;
	};
}