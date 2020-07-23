#pragma once
#include "SEObject.h"

namespace Spartan
{
#ifdef _DEBUG
	class BaseConsoleCommand;

	struct QueudCommand
	{
		string Command;
		vector<string> Args;
		bool CommandIsWaiting = false;
	};

	class ConsoleInput : SEObject
	{
	public:
		ConsoleInput();
		~ConsoleInput();

		void Initialize();
		void WaitForInput();
		bool Running();
		void Stop();
		void Update();

		void RegisterCommand(BaseConsoleCommand* pCommand);

		virtual const std::type_info& GetBaseType() { return typeid(ConsoleInput); }
		virtual const std::type_info& GetType() { return typeid(ConsoleInput); }

	private:
		void ProcessInput(const std::string& input);
		void SeperateArguments(const std::string& input, std::string& command, std::vector<string>& args);

		BaseConsoleCommand* GetCommand(const std::string& command);

	private:
		SDL_Thread* m_pConsoleThread;
		std::vector<BaseConsoleCommand*> m_pCommands;
		QueudCommand m_QueuedCommand;
		bool m_Running;
		bool m_Writing = false;
		bool m_Reading = false;
	};
#endif // _DEBUG
}