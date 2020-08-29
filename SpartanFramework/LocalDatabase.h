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

	private:
		LocalDatabase(const char* path);
		~LocalDatabase();

		bool Open();
		void Close();

		static int SQLiteCallback(void* NotUsed, int argc, char** argv, char** azColName);

	private:
		const char* m_Path;
		sqlite3* m_pSQLite;
		char* m_pLastError;
	};
}