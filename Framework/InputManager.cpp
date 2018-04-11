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
}

void InputManager::KeyDown(SDL_KeyboardEvent *keyboardEvent)
{
	SDL_Keysym *key = &keyboardEvent->keysym;

	// Find the key
	auto it = find_if(m_InputActions.begin(), m_InputActions.end(), [key](InputAction &inputAction)
	{
		return (key->sym == inputAction.Key || key->mod == inputAction.KeyMod);
	});

	if (it == m_InputActions.end())
		return;

	auto action = &*it;

	switch (action->Type)
	{
	case Pressed:
		if(!action->m_bTriggeredLastFrame)
			action->m_bIsTriggered = true;
		else
			action->m_bIsTriggered = false;

		action->m_bTriggeredLastFrame = true;

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
		return (key->sym == inputAction.Key || key->mod == inputAction.KeyMod);
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
