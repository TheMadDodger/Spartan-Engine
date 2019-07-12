#pragma once
#include "stdafx.h"
#include "ConsoleInput.h"

#ifdef _DEBUG
class BaseConsoleCommand
{
public:
	BaseConsoleCommand(const std::string &command) : m_Command(command) {}
	~BaseConsoleCommand() {}

	const std::string &GetCommand()
	{
		return m_Command;
	}

protected:
	template<typename T>
	T Parse(const std::string &value)
	{
		T data;

		try
		{
			if (typeid(T) == typeid(int))
			{
				int i = stoi(value.data());
				memcpy((char*)&data, (char*)&i, sizeof(T));
			}
			else if (typeid(T) == typeid(char*))
			{
				memcpy((char*)&data, (const char*)value.data(), value.length());
			}
			else if (typeid(T) == typeid(float))
			{
				float f = stof(value.data());
				memcpy((char*)&data, (char*)&f, sizeof(T));
			}
			else if (typeid(T) == typeid(double))
			{
				double d = stod(value);
				memcpy((char*)&data, (char*)&d, sizeof(T));
			}
			else if (typeid(T) == typeid(unsigned int))
			{
				unsigned int ui = (unsigned int)stoi(value);
				memcpy((char*)&data, (char*)&ui, sizeof(T));
			}
		}
		catch (const std::exception &e)
		{
			Utilities::Debug::LogWarning("Couldnt parse " + value + " in command.");
			Utilities::Debug::LogWarning(e.what());
		}

		return data;
	}

private:
	virtual bool RootExecuteCommand(const std::vector<string> &args) = 0;

private:
	friend class ConsoleInput;
	const std::string m_Command;
};

template<typename A1>
class ConsoleCommand : public BaseConsoleCommand
{
public:
	ConsoleCommand(const std::string &command) : BaseConsoleCommand(command) {}
	virtual ~ConsoleCommand() {}

protected:
	virtual bool ExecuteCommand(A1 arg1) = 0;

private:
	virtual bool RootExecuteCommand(const std::vector<string> &args) override
	{
		if (!UnpackArguments(args)) return false;
		//CallFunc(m_Arguments, std::index_sequence_for<Args...>());

		return ExecuteCommand(m_Argument1);
	}

	bool UnpackArguments(const vector<string> &arguments)
	{
		if (arguments.size() <= 0) return false;

		m_Argument1 = Parse<A1>(arguments[0]);
	}

	/*template<std::size_t... Is>
	void CallFunc(const std::tuple<Args...>& tuple,
		std::index_sequence<Is...>)
	{
		ExecuteCommand(std::get<Is>(tuple)...);
	}*/

private:
	A1 m_Argument1;
};

template<typename A1, typename A2>
class ConsoleCommand2 : public BaseConsoleCommand
{
public:
	ConsoleCommand2(const std::string &command) : BaseConsoleCommand(command) {}
	virtual ~ConsoleCommand2() {}

protected:
	virtual bool ExecuteCommand(A1 arg1, A2 arg2) = 0;

private:
	virtual bool RootExecuteCommand(const std::vector<string> &args) override
	{
		if (!UnpackArguments(args)) return false;

		return ExecuteCommand(m_Argument1, m_Argument2);
	}

	bool UnpackArguments(const vector<string> &arguments)
	{
		if (arguments.size() <= 0) return false;

		m_Argument1 = Parse<A1>(arguments[0]);
		m_Argument2 = Parse<A2>(arguments[1]);
	}

private:
	A1 m_Argument1;
	A2 m_Argument2;
};

class TestCommand : public ConsoleCommand2<const char *, float>
{
public:
	TestCommand() : ConsoleCommand2<const char *, float>("test") {}
	virtual ~TestCommand() {}

private:
	virtual bool ExecuteCommand(const char *s, float f) override
	{
		Utilities::Debug::LogNotice(std::string(s) + ": " + to_string(f));
		return true;
	}
};
#endif // _DEBUG