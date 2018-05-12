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

void InputManager::AddInputAction(const InputAction &inputAction)
{
	// Add this new InputAction to the vector
	m_InputActions.push_back(inputAction);
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

const Vector2 InputManager::GetMouseWorldPosition(Matrix3X3 &cameraMatrix)
{
	Vector3 transVec = Vector3(m_MousePosition.x, m_MousePosition.y, 1.0f);
	auto transPos = cameraMatrix * transVec;
	return Vector2(transPos.x, transPos.y);
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
