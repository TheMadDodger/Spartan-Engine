#pragma once
#include "SEObject.h"

namespace Spartan
{
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

			template <typename T> static T Read(const char* buffer)
			{
				// Make sure the user is not trying to read a string
				if (typeid(T) == typeid(std::string))
				{
					//std::cout << "BinaryContainer::Read<T>() > Please use BinaryContainer::ReadString() instead for reading strings!" << std::end;
				}

				// Read the data
				T data;

				//data = static_cast<T>(&buffer[m_BufferReadPos]);

				memcpy(&data, &buffer[m_BufferReadPos], sizeof(T));

				m_BufferReadPos += sizeof(T);
				return data;
			}

			static const string ReadString(const char* buffer);
			static void ResetReadPosition() { m_BufferReadPos = 0; }

			// Writing
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
			static void WriteString(const string& data);

			static void CreateDir(LPCSTR path);
			static int GetReadPosition()
			{
				return m_BufferReadPos;
			}

			static std::string ReadCompleteFile(const char* file)
			{
				int index = 0;
				if (!BinaryContainer::OpenRead(file))
				{
					Debug::LogWarning("Error when trying to read file: " + std::string(file));
					return "";
				}
				std::string fileOutput;
				while (!BinaryContainer::ReachedEndOfFile())
				{
					char c = BinaryContainer::Read<char>();
					fileOutput += c;
					++index;
				}
				BinaryContainer::Close();
				return fileOutput;
			}

		private:
			static std::ifstream* m_piFileStream;
			static std::ofstream* m_poFileStream;
			static bool m_ReadWrite;

			static int m_BufferReadPos;

		private:
			BinaryContainer() {};
			~BinaryContainer() {};
		};
	}
}