#include "stdafx.h"
#include "ConsoleInput.h"
#include "Commands.h"

namespace SpartanEngine
{
#ifdef _DEBUG
	inline int ConsoleThreadFunc(void* pConsoleObject)
	{
		ConsoleInput* pConsole = (ConsoleInput*)pConsoleObject;

		while (pConsole->Running())
		{
			pConsole->WaitForInput();
		}

		return 0;
	}

	ConsoleInput::ConsoleInput()
	{
	}

	ConsoleInput::~ConsoleInput()
	{
		for (auto pCommand : m_pCommands)
		{
			delete pCommand;
		}
		m_pCommands.clear();

		Parser::Destroy();
	}

	void ConsoleInput::Initialize()
	{
		m_Running = true;
		m_pConsoleThread = SDL_CreateThread(ConsoleThreadFunc, "ConsoleThread", this);
	}

	void ConsoleInput::WaitForInput()
	{
		std::string line = "";
		getline(cin, line);

		ProcessInput(line);
	}

	bool ConsoleInput::Running()
	{
		return m_Running;
	}

	void ConsoleInput::Stop()
	{
		m_Running = false;
	}

	void ConsoleInput::Update()
	{
		if (m_Writing) return;

		m_Reading = true;
		if (m_QueuedCommand.CommandIsWaiting)
		{
			BaseConsoleCommand* pCommand = GetCommand(m_QueuedCommand.Command);

			if (pCommand != nullptr)
			{
				if (!pCommand->RootExecuteCommand(m_QueuedCommand.Args))
					Utilities::Debug::LogNotice(">>>> Invalid argument count!", false);
			}
			else
				Utilities::Debug::LogNotice(">>>> Unknown Command detected!", false);

			m_QueuedCommand.CommandIsWaiting = false;
		}
		m_Reading = false;
	}

	void ConsoleInput::RegisterCommand(BaseConsoleCommand* pCommand)
	{
		m_pCommands.push_back(pCommand);
	}

	void ConsoleInput::ProcessInput(const std::string& input)
	{
		if (input == "") return;

		while (m_Reading)
		{
			// Do nothing
		}

		m_Writing = true;
		SeperateArguments(input, m_QueuedCommand.Command, m_QueuedCommand.Args);

		m_QueuedCommand.CommandIsWaiting = true;
		m_Writing = false;
	}

	void ConsoleInput::SeperateArguments(const std::string& input, std::string& command, std::vector<string>& args)
	{
		command = "";
		args.clear();

		int argNumber = 0;
		string currentArg = "";
		for (size_t i = 0; i < input.size(); i++)
		{
			char c = input[i];
			if (c != ' ')
			{
				currentArg.push_back(c);

				if (i == input.size() - 1)
				{
					if (argNumber == 0)
					{
						command = currentArg;
						currentArg = "";
						++argNumber;
						continue;
					}
					args.push_back(currentArg);
					currentArg = "";
					++argNumber;
				}
			}
			else
			{
				if (argNumber == 0)
				{
					command = currentArg;
					currentArg = "";
					++argNumber;
					continue;
				}
				args.push_back(currentArg);
				currentArg = "";
				++argNumber;
			}
		}
	}

	BaseConsoleCommand* ConsoleInput::GetCommand(const std::string& command)
	{
		auto it = std::find_if(m_pCommands.begin(), m_pCommands.end(), [&](BaseConsoleCommand* pCommand)
		{
			if (pCommand->GetCommand() == command) return true;
			return false;
		});

		if (it == m_pCommands.end()) return nullptr;
		BaseConsoleCommand* pCommand = *it;
		return pCommand;
	}
#endif // _DEBUG
}