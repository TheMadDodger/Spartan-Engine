#pragma once

namespace Utilities
{
	class BinaryContainer
	{
	public:
		// Closing
		static void Close();

		// Read operations
		static bool OpenRead(const char* file);
		template <typename T> static T Read()
		{
			// Safety checks
			if (m_piFileStream == nullptr)
			{
				Debug::LogWarning("BinaryContainer::Read<T>() > No file was opened for reading!");
			}
			if (!m_piFileStream->is_open())
			{
				Debug::LogWarning("BinaryContainer::Read<T>() > No file was opened for reading!");
			}

			// Check if the file was opened for reading
			if (m_ReadWrite)
			{
				Debug::LogWarning("BinaryContainer::Read<T>() > File was not opened for reading!");
			}

			// Make sure the use is not trying to read a string
			if (typeid(T) == typeid(std::string))
			{
				Debug::LogWarning("BinaryContainer::Read<T>() > Please use BinaryContainer::ReadString() instead for reading strings!");
			}

			// Read the data
			T data;
			m_piFileStream->read((char*)&data, sizeof(T));
			return data;
		}
		static const string ReadString();
		static const string ReadStringWidthLength(int length);
		static bool ReachedEndOfFile();

		// Writing TODO
		static bool OpenWrite(const char* file);
		template <typename T> static void Write(T data)
		{
			// Safety checks
			if (m_poFileStream == nullptr)
			{
				Debug::LogWarning("BinaryContainer::Write<T>() > No file was opened for writing!");
				return;
			}
			if (!m_poFileStream->is_open())
			{
				Debug::LogWarning("BinaryContainer::Write<T>() > No file was opened for writing!");
				return;
			}

			// Check if the file was opened for writing
			if (!m_ReadWrite)
			{
				Debug::LogWarning("BinaryContainer::Write<T>() > File was not opened for writing!");
				return;
			}

			// Make sure the use is not trying to read a string
			if (typeid(T) == typeid(std::string))
			{
				Debug::LogWarning("BinaryContainer::Write<T>() > Please use BinaryContainer::ReadString() instead for reading strings!");
				return;
			}

			// Write the data
			m_poFileStream->write((char*)&data, sizeof(T));
		}
		static void WriteString(const string &data);

	private:
		static std::ifstream *m_piFileStream;
		static std::ofstream *m_poFileStream;
		static bool m_ReadWrite;

	private:
		BinaryContainer() {};
		~BinaryContainer() {};
	};
}