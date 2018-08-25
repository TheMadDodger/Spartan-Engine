#include "stdafx.h"
#include "BinaryContainer.h"

using namespace Utilities;

std::ifstream *BinaryContainer::m_piFileStream = nullptr;
std::ofstream *BinaryContainer::m_poFileStream = nullptr;
bool BinaryContainer::m_ReadWrite = false;

void BinaryContainer::Close()
{
	if (m_piFileStream != nullptr)
	{
		if (m_piFileStream->is_open())
		{
			m_piFileStream->close();
		}

		delete m_piFileStream;
		m_piFileStream = nullptr;
	}

	if (m_poFileStream != nullptr)
	{
		if (m_poFileStream->is_open())
		{
			m_poFileStream->close();
		}

		delete m_poFileStream;
		m_poFileStream = nullptr;
	}
}

#pragma region BinaryContainer::Reading

bool BinaryContainer::OpenRead(const char *file)
{
	if (m_piFileStream == nullptr)
	{
		m_piFileStream = new std::ifstream();
	}
	m_piFileStream->open(file, ios::binary | ios::in);

	m_ReadWrite = false;

	return m_piFileStream->is_open();
}

const string BinaryContainer::ReadString()
{
	// Safety checks
	if (m_piFileStream == nullptr)
	{
		cout << "BinaryContainer::Read<T>() > No file was opened for reading!" << endl;
		return "";
	}
	if (!m_piFileStream->is_open())
	{
		cout << "BinaryContainer::Read<T>() > No file was opened for reading!" << endl;
		return "";
	}

	// Check if the file was opened for reading
	if (m_ReadWrite)
	{
		cout << "BinaryContainer::Read<T>() > File was not opened for reading!" << endl;
		return "";
	}

	// Continue to read chars untill the string nullifier '\0' is found
	string data = "";
	char c = ' ';
	while (c != '\0')
	{
		c = Read<char>();
		data += c;
	}

	data.erase(data.end() - 1);

	return data;
}

const string BinaryContainer::ReadStringWidthLength(int length)
{
	// Safety checks
	if (m_piFileStream == nullptr)
	{
		cout << "BinaryContainer::Read<T>() > No file was opened for reading!" << endl;
		return "";
	}
	if (!m_piFileStream->is_open())
	{
		cout << "BinaryContainer::Read<T>() > No file was opened for reading!" << endl;
		return "";
	}

	// Check if the file was opened for reading
	if (m_ReadWrite)
	{
		cout << "BinaryContainer::Read<T>() > File was not opened for reading!" << endl;
		return "";
	}

	// Read char* with given length
	string data = "";
	char* c = new char();
	m_piFileStream->read(c, length);
	data = string(c);

	delete c;

	return data;
}

bool BinaryContainer::ReachedEndOfFile()
{
	// Check if the file was opened for reading
	if (m_ReadWrite)
	{
		cout << "BinaryContainer::Read<T>() > File was not opened for reading!" << endl;
		return false;
	}

	if (m_piFileStream != nullptr)
	{
		if (m_piFileStream->is_open())
		{
			return m_piFileStream->eof();
		}
	}
	return false;
}

#pragma endregion

#pragma region BinaryContainer::Writing

bool BinaryContainer::OpenWrite(const char *file)
{
	if (m_poFileStream == nullptr)
	{
		m_poFileStream = new std::ofstream();
	}

	try
	{
		m_poFileStream->open(file, ios::binary | ios::out);
	}
	catch (const std::exception&e)
	{
		cout << e.what() << endl;
	}

	m_ReadWrite = true;

	return m_poFileStream->is_open();
}

void Utilities::BinaryContainer::WriteString(const string &data)
{
	for (char c : data)
	{
		Write<char>(c);
	}
	Write<char>('\0');
}

#pragma endregion