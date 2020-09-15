#pragma once
#include "SEObject.h"
#include "SQLCmdDefs.h"

#define LITERALSTRING(str) #str

namespace Spartan
{
	class LocalDatabase
	{
	public:
		static LocalDatabase* BeginDatabase(const char* path);
		static void EndDatabase(LocalDatabase* pInstance);

		bool CreateTable(const SQLCreateTableDef& tableDef);

		bool ExecuteRawCommand(const std::string& cmd);

		bool Select(const std::string& tableName, const std::string& range = "*", const std::string& querry = "");

		const SQLSelectResult& GetSelectResult() const;

	private:
		LocalDatabase(const char* path);
		~LocalDatabase();

		bool Open();
		void Close();

		static int SQLiteCallback(void* data, int argc, char** argv, char** azColName);
		static int SQLSelectCallback(void* data, int argc, char** argv, char** azColName);

	private:
		const char* m_Path;
		sqlite3* m_pSQLite;
		char* m_pLastError;
		SQLSelectResult m_LastSelectResult;
	};
}