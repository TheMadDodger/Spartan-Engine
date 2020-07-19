#include "stdafx.h"
#include "Debug.h"

namespace Spartan
{
	namespace Utilities
	{
		std::string AutomaticLogger::m_NextMessagePrefix = "";
		vector<LoggingData> AutomaticLogger::m_DataToLog = vector<LoggingData>();
		bool Debug::m_PhysicsDebugRendering = false;
		std::ofstream Debug::m_File = std::ofstream();

		void Debug::Log(const std::string& message, const LogLevel& logLevel, bool bIncludeTimeStamp)
		{
			switch (logLevel)
			{
			case LogLevel::Info:
				LogInfo(message, bIncludeTimeStamp);
				break;

			case LogLevel::Notice:
				LogNotice(message, bIncludeTimeStamp);
				break;

			case LogLevel::Warning:
				LogWarning(message, bIncludeTimeStamp);
				break;

			case LogLevel::Error:
				LogError(message, bIncludeTimeStamp);
				break;
			default:
				break;
			}
		}

		void Utilities::Debug::LogInfo(const std::string& message, bool bIncludeTimeStamp)
		{
			SetConsoleColor(15);
			if (bIncludeTimeStamp)
				TimeStamp();
			std::cout << "Info:	" << message << endl;

			if (m_File.is_open())
			{
				m_File << "Info:	" << message << endl;
			}
			ResetConsoleColor();
		}

		void Utilities::Debug::LogNotice(const std::string& message, bool bIncludeTimeStamp)
		{
			SetConsoleColor(8);
			if (bIncludeTimeStamp)
				TimeStamp();
			std::cout << "Notice:	" << message << endl;

			if (m_File.is_open())
			{
				m_File << "Notice:	" << message << endl;
			}
			ResetConsoleColor();
		}

		void Utilities::Debug::LogWarning(const std::string& message, bool bIncludeTimeStamp)
		{
			SetConsoleColor(14);
			if (bIncludeTimeStamp)
				TimeStamp();
			std::cout << "WARNING:	" << message << endl;

			if (m_File.is_open())
			{
				m_File << "WARNING:	" << message << endl;
			}
			ResetConsoleColor();
		}

		void Utilities::Debug::LogError(const std::string& message, bool bIncludeTimeStamp)
		{
			SetConsoleColor(12);
			if (bIncludeTimeStamp)
				TimeStamp();
			std::cout << "ERROR:	" << message << endl;

			if (m_File.is_open())
			{
				m_File << "ERROR:	" << message << endl;
			}
			ResetConsoleColor();

			//TODO: Open dialoge box
			const SDL_MessageBoxButtonData buttons[] = {
				{ /* .flags, .buttonid, .text */        0, 0, "OK" },
			};
			const SDL_MessageBoxColorScheme colorScheme =
			{
				{ /* .colors (.r, .g, .b) */
				  /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
					{ 255, 255, 255 },
					/* [SDL_MESSAGEBOX_COLOR_TEXT] */
					{ 0, 0, 0 },
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
					{ 0, 0, 0 },
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
					{ 255, 255, 255 },
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
					{ 128, 128, 128 }
				}
			};
			const SDL_MessageBoxData messageboxdata = {
				SDL_MESSAGEBOX_ERROR, /* .flags */
				NULL, /* .window */
				"ERROR", /* .title */
				message.data(), /* .message */
				SDL_arraysize(buttons), /* .numbuttons */
				buttons, /* .buttons */
				&colorScheme /* .colorScheme */
			};
			int buttonid;
			if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
				SDL_Log("error displaying message box");
			}

			BaseGame::GetGame()->QuitGame();
		}

		void Utilities::Debug::LogGLError(const GLenum& err, bool bIncludeTimeStamp)
		{
			if (err != GL_NO_ERROR)
			{
				const char* error = (const char*)glewGetErrorString(err);
				Utilities::Debug::LogWarning(error, bIncludeTimeStamp);
			}
		}

		void Utilities::Debug::EnablePhysicsDebugRendering(bool enable)
		{
			m_PhysicsDebugRendering = enable;
		}

		bool Utilities::Debug::CanRenderDebug()
		{
			return m_PhysicsDebugRendering;
		}

		void Utilities::Debug::TimeStamp()
		{
			auto t = time(nullptr);
			tm tM;
			localtime_s(&tM, &t);
			cout << "[" << put_time(&tM, "%d-%m-%Y %H-%M-%S") << "] ";
		}
	}
}