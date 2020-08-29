#include "stdafx.h"
#include "LocalDatabase.h"
#include "Debug.h"


#define SQLCHECK_ERROR(rc) if(rc != SQLITE_OK) \
{ \
	Utilities::Debug::LogWarning("SQL error: " + std::string(m_pLastError));\
	sqlite3_free(m_pLastError); \
	return false;\
}

#define SQLITE_COMMAND(cmd, data) sqlite3_exec(m_pSQLite, cmd, SQLiteCallback, data, &m_pLastError)

namespace Spartan
{
	LocalDatabase* LocalDatabase::BeginDatabase(const char* path)
	{
		LocalDatabase* pInstance = new LocalDatabase(path);
		if (!pInstance->Open())
		{
			delete pInstance;
			pInstance = nullptr;
			return nullptr;
		}
		return pInstance;
	}

	void LocalDatabase::EndDatabase(LocalDatabase* pInstance)
	{
		pInstance->Close();
		delete pInstance;
		pInstance = nullptr;
	}

	bool LocalDatabase::CreateTable(const SQLCreateTableDef& tableDef)
	{
		std::string cmd = tableDef.CreateCommand();
		SQLCHECK_ERROR(SQLITE_COMMAND(cmd.c_str(), 0));
		Utilities::Debug::LogInfo("SQL: Table " + tableDef.Name + " Created");
		return true;
	}

	LocalDatabase::LocalDatabase(const char* path) : m_Path(path), m_pLastError(NULL), m_pSQLite(nullptr)
	{
	}

	LocalDatabase::~LocalDatabase()
	{
	}

	bool LocalDatabase::Open()
	{
		SQLCHECK_ERROR(sqlite3_open(m_Path, &m_pSQLite));
		return true;
	}

	void LocalDatabase::Close()
	{
		sqlite3_close(m_pSQLite);
	}

	int LocalDatabase::SQLiteCallback(void* data, int argc, char** argv, char** azColName)
	{
		int i;
		for (i = 0; i < argc; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}
		printf("\n");
		return 0;
	}
}