#include "stdafx.h"
#include "../stdafx.h"
#include "InputManager.h"


InputManager::InputManager() : m_InputActions(vector<InputAction>())
{
}

InputManager::~InputManager()
{
	m_InputActions.clear();
}

InputAction &InputManager::AddInputAction(const InputAction &inputAction)
{
	// Add this new InputAction to the vector
	m_InputActions.push_back(inputAction);
	return m_InputActions[m_InputActions.size() - 1];
}

bool InputManager::IsActionTriggered(const string &actionName)
{
	// First find if the provided action exists
	auto it = find_if(m_InputActions.begin(), m_InputActions.end(), [actionName](const InputAction &action)
	{
		return(action.ActionName == actionName);
	});

	if (it == m_InputActions.end())
	{
		// Action doesn't exist
		Utilities::Debug::Log("InputManager::IsActionTriggered > InputAction " + actionName + " does not exist!", Utilities::LogLevel::Warning);
		return false;
	}

	// Get the InputAction object
	auto action = *it;
	return action.m_bIsTriggered;
}

void InputManager::ReplaceInputAction(const string & actionName, const InputAction &inputAction)
{
	// First find if the provided action exists
	auto it = find_if(m_InputActions.begin(), m_InputActions.end(), [actionName](const InputAction &action)
	{
		return(action.ActionName == actionName);
	});

	if (it == m_InputActions.end())
	{
		// Action doesn't exist
		Utilities::Debug::Log("InputManager::ReplaceInputAction > InputAction " + actionName + " does not exist!", Utilities::LogLevel::Warning);
		return;
	}

	*it = inputAction;
}

const Vector2 InputManager::GetMouseWorldPosition(Matrix3X3 &cameraMatrix)
{
	Vector3 transVec = Vector3(m_MousePosition.x, m_MousePosition.y, 1.0f);
	auto transPos = cameraMatrix * transVec;
	return Vector2(transPos.x, transPos.y);
}

Vector2 InputManager::GetControllerJoystickPosition(DWORD controllerID, const JoystickType &stick)
{
	if (controllerID > XUSER_MAX_COUNT || controllerID < 0)
	{
		Utilities::Debug::Log("InputManager::GetControllerJoystickPosition > Controller " + to_string(controllerID) + " out of range.", Utilities::LogLevel::Warning);
		return Vector2::Zero();
	}

	XINPUT_STATE state;

	if (XInputGetState(controllerID, &state) == ERROR_SUCCESS)
	{
		// Raw Input Data
		Vector2 result = Vector2::Zero();
		switch (stick)
		{
		case JoystickType::LeftThumbStick:
			result.x = state.Gamepad.sThumbLX;
			result.y = state.Gamepad.sThumbLY;
			break;

		case JoystickType::RightThumbStick:
			result.x = state.Gamepad.sThumbRX;
			result.y = state.Gamepad.sThumbRY;
			break;

		case JoystickType::Trigger:
			result.x = state.Gamepad.bLeftTrigger;
			result.y = state.Gamepad.bRightTrigger;
			break;
		}

		// Apply Dead Zone
		float magnitude = result.Normalize();
		if (magnitude > INPUT_DEADZONE)
		{
			// Clip to maximum
			if (magnitude > MAX_STICK_MAGNITUDE) magnitude = MAX_STICK_MAGNITUDE;

			magnitude -= INPUT_DEADZONE;
		}
		else
		{
			magnitude = 0.0f;
		}
		result = result * magnitude;

		return result;
	}
	else
	{
		Utilities::Debug::Log("InputManager::GetControllerJoystickPosition > Controller " + to_string(controllerID) + " is not connected.", Utilities::LogLevel::Warning);
		return Vector2::Zero();
	}
}

void InputManager::Update()
{
	for_each(m_InputActions.begin(), m_InputActions.end(), [](InputAction &inputAction)
	{
		switch (inputAction.Type)
		{
		case Down:
			// Let KeyUp update this
			break;
		case Pressed:
			// Reset
			inputAction.m_bIsTriggered = false;
			break;

		case Released:
			// Reset
			inputAction.m_bIsTriggered = false;
			break;
		default:
			break;
		}
	});

	m_LastFrameWheelData = Vector2::Zero();

	ControllerUpdate();
}

void InputManager::ControllerUpdate()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		XINPUT_STATE state = {};
		
		DWORD result = XInputGetState(i, &state);

		if (result == ERROR_SUCCESS)
		{
			for_each(m_InputActions.begin(), m_InputActions.end(), [&state, i](InputAction &inputAction)
			{
				if (inputAction.ControllerID == i)
				{
					if (inputAction.ControllerButton != 0)
					{
						if (state.Gamepad.wButtons & inputAction.ControllerButton)
						{
							switch (inputAction.Type)
							{
							case Down:
								inputAction.m_bIsTriggered = true;
								break;
							case Pressed:
								// Reset
								//inputAction.m_bIsTriggered = false;
								break;

							case Released:
								// Reset
								//inputAction.m_bIsTriggered = false;
								break;
							default:
								break;
							}
						}
						else
						{
							switch (inputAction.Type)
							{
							case Down:
								inputAction.m_bIsTriggered = false;
								break;
							case Pressed:
								// Reset
								//inputAction.m_bIsTriggered = false;
								break;

							case Released:
								// Reset
								//inputAction.m_bIsTriggered = false;
								break;
							default:
								break;
							}
						}
					}
				}
			});
		}
	}
}

void InputManager::KeyDown(SDL_KeyboardEvent *keyboardEvent)
{
	SDL_Keysym *key = &keyboardEvent->keysym;

	// Find the key
	auto it = find_if(m_InputActions.begin(), m_InputActions.end(), [key](InputAction &inputAction)
	{
		if (key->sym == inputAction.Key || key->scancode == inputAction.KeyMod)
		{
			return true;
		}
		else
		{
			return false;
		}
	});

	if (it == m_InputActions.end())
		return;

	auto action = &*it;

	switch (action->Type)
	{
	case Pressed:
		if (!action->m_bTriggeredLastFrame)
		{
			action->m_bIsTriggered = true;
			action->m_bTriggeredLastFrame = true;
		}
		break;

	case Down:
		action->m_bIsTriggered = true;
		break;

	case Released:
		action->m_bIsTriggered = false;
		break;
	}
}

void InputManager::KeyUp(SDL_KeyboardEvent *keyboardEvent)
{
	SDL_Keysym *key = &keyboardEvent->keysym;

	// Find the key
	auto it = find_if(m_InputActions.begin(), m_InputActions.end(), [key](InputAction &inputAction)
	{
		return (key->sym == inputAction.Key || key->scancode == inputAction.KeyMod);
	});

	if (it == m_InputActions.end())
		return;

	auto action = &*it;

	switch (action->Type)
	{
	case Pressed:
	case Down:
		action->m_bIsTriggered = false;
		action->m_bTriggeredLastFrame = false;
		break;

	case Released:
		action->m_bIsTriggered = true;
		break;
	}
}

void InputManager::MouseUp(SDL_MouseButtonEvent *mouseButtonEvent)
{
	auto button = mouseButtonEvent->button;

	// Find the button
	auto it = find_if(m_InputActions.begin(), m_InputActions.end(), [button](InputAction &inputAction)
	{
		return (button == inputAction.MouseButton);
	});

	if (it == m_InputActions.end())
		return;

	auto action = &*it;

	switch (action->Type)
	{
	case Pressed:
	case Down:
		action->m_bIsTriggered = false;
		action->m_bTriggeredLastFrame = false;
		break;

	case Released:
		action->m_bIsTriggered = true;
		break;
	}
}

void InputManager::MouseDown(SDL_MouseButtonEvent *mouseButtonEvent)
{
	auto button = mouseButtonEvent->button;

	// Find the button
	auto it = find_if(m_InputActions.begin(), m_InputActions.end(), [button](InputAction &inputAction)
	{
		return (button == inputAction.MouseButton);
	});

	if (it == m_InputActions.end())
		return;

	auto action = &*it;

	switch (action->Type)
	{
	case Pressed:
		if (!action->m_bTriggeredLastFrame)
		{
			action->m_bIsTriggered = true;
			action->m_bTriggeredLastFrame = true;
		}
		break;

	case Down:
		action->m_bIsTriggered = true;
		break;

	case Released:
		action->m_bIsTriggered = false;
		break;
	}
}

void InputManager::HandleMouseMotionEvent(SDL_MouseMotionEvent *mouseMotionEvent, int windowHieght)
{
	m_MousePosition = Vector2((float)mouseMotionEvent->x, (float)windowHieght - (float)mouseMotionEvent->y);
}

void InputManager::HandleMouseScrollEvent(SDL_MouseWheelEvent *mouseWheelEvent)
{
	m_LastFrameWheelData = Vector2((float)mouseWheelEvent->x, (float)mouseWheelEvent->y);
}
