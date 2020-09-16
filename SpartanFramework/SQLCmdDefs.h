#pragma once

namespace Spartan
{
	struct SQLTableKeyData
	{
		std::string Name;
		std::string Type;
		std::vector<std::string> Attributes;
	};

	struct SQLCreateTableDef
	{
	public:
		std::string Name;
		std::vector<SQLTableKeyData> Keys;

		std::string CreateCommand() const
		{
			std::string command = "CREATE TABLE " + Name + "(";

			for (size_t i = 0; i < Keys.size(); i++)
			{
				command += Keys[i].Name + " " + Keys[i].Type + " ";

				for (size_t j = 0; j < Keys[i].Attributes.size(); j++)
				{
					command += Keys[i].Attributes[j] + "	";
				}

				if (i < Keys.size() - 1) command += ",";
			}
			command += ");";

			return command;
		}
	};

	struct SQLSelectDef
	{
		std::string Range;
		std::string TableName;
	};

	struct SQLSelectResult
	{
		std::vector<std::map<std::string, std::string>> Data;
	};
}