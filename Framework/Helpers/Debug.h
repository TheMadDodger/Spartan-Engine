#pragma once

#define GET_VARIABLE_NAME(Variable) (#Variable)

namespace Utilities
{
	enum LogLevel
	{
		Info, // Normal debug info for debugging
		Notice, // A notice for things that still have to be done, bug fixes, changes, additions etc
		Warning, // A warning will be displayed in yellow but app keeps running
		Error, // An error will display the error in a seperate window and then close the game
	};

	class LoggingData
	{
	public:
		LoggingData(const float *pDataToLog, float logInterval)
			: m_pfDataToLog(pDataToLog), m_LogInterval(logInterval), m_Type(DFLOAT) {}

		LoggingData(const int *pDataToLog, float logInterval)
			: m_piDataToLog(pDataToLog), m_LogInterval(logInterval), m_Type(DINT) {}

		LoggingData(const bool *pDataToLog, float logInterval)
			: m_pbDataToLog(pDataToLog), m_LogInterval(logInterval), m_Type(DBOOL) {}

		LoggingData(const double *pDataToLog, float logInterval)
			: m_pdDataToLog(pDataToLog), m_LogInterval(logInterval), m_Type(DDOUBLE) {}

	private:
		friend class AutomaticLogger;
		const float *m_pfDataToLog = nullptr;
		const int *m_piDataToLog = nullptr;
		const bool *m_pbDataToLog = nullptr;
		const double *m_pdDataToLog = nullptr;
		float m_LogInterval = 0.0f; // Interval in seconds
		float m_PersonalTimer = 0.0f;
		std::string m_MessagePrefix = "";

		enum DataType
		{
			DINT,
			DDOUBLE,
			DBOOL,
			DFLOAT,
			ERRORTYPE,
		};

		DataType m_Type = ERRORTYPE;
	};

	class AutomaticLogger
	{
	private:
		friend class Debug;
		//AutomaticLogger() : m_DataToLog(vector<LoggingData>()) {}

		static void Update(Time *pTime)
		{
			for (auto &pData : m_DataToLog)
			{
				//if (pData.m_PersonalTimer = 0.0f) pData.m_PersonalTimer = pTime->GetTime();
				if (pData.m_PersonalTimer <= pTime->GetTime() - pData.m_LogInterval)
				{
					std::string msg;
					switch (pData.m_Type)
					{
					case LoggingData::DBOOL:
						msg = (*pData.m_pbDataToLog == true) ? "ENABLED" : "DISABLED";
						cout << pData.m_MessagePrefix << " " << msg << endl;
						break;

					case LoggingData::DDOUBLE:
						msg = std::to_string(*pData.m_pdDataToLog);
						cout << pData.m_MessagePrefix << " " << msg << endl;
						break;

					case LoggingData::DFLOAT:
						msg = std::to_string(*pData.m_pfDataToLog);
						cout << pData.m_MessagePrefix << " " << msg << endl;
						break;

					case LoggingData::DINT:
						msg = std::to_string(*pData.m_piDataToLog);
						cout << pData.m_MessagePrefix << " " << msg << endl;
						break;
					default:
						break;
					}

					pData.m_PersonalTimer = pTime->GetTime();
				}
			}
		}

		static void Append(LoggingData *pLoggingData)
		{
			pLoggingData->m_MessagePrefix = m_NextMessagePrefix;
			m_DataToLog.push_back(*pLoggingData);
		}

	private:
		static vector<LoggingData> m_DataToLog;
		static std::string m_NextMessagePrefix;
	};

	class Debug
	{
	public:
		static void Log(const std::string &message, const LogLevel &logLevel, bool bIncludeTimeStamp = true);
		static void LogInfo(const std::string &message, bool bIncludeTimeStamp = true);
		static void LogNotice(const std::string &message, bool bIncludeTimeStamp = true);
		static void LogWarning(const std::string &message, bool bIncludeTimeStamp = true);
		static void LogError(const std::string &message, bool bIncludeTimeStamp = true);
		static void UpdateAutoLogger(Time *pTime) { AutomaticLogger::Update(pTime); }  //{ m_pAutomaticLogger->Update(pTime); }

		static void EnablePhysicsDebugRendering(bool enable);
		static bool CanRenderDebug();

		static void LogAutomaticData(const float *pDataToLog, float interval)
		{
			auto loggingData = LoggingData(pDataToLog, interval);
			AutomaticLogger::Append(&loggingData);
		}

		static void SetNextMessagePrefix(const std::string &prefix)
		{
			AutomaticLogger::m_NextMessagePrefix = prefix;
		}

	private:
		static void TimeStamp();
		static bool m_PhysicsDebugRendering;
	};

	inline void SetConsoleColor(WORD color)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, color);
	}

	inline void ResetConsoleColor()
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, 15);
	}
}

