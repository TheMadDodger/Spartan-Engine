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
				//std::cout << "BinaryContainer::Read<T>() > No file was opened for reading!" << std::end;
			}
			if (!m_piFileStream->is_open())
			{
				//std::cout << "BinaryContainer::Read<T>() > No file was opened for reading!" << std::end;
			}

			// Check if the file was opened for reading
			if (m_ReadWrite)
			{
				//std::cout << "BinaryContainer::Read<T>() > File was not opened for reading!" << std::end;
			}

			// Make sure the user is not trying to read a string
			if (typeid(T) == typeid(std::string))
			{
				//std::cout << "BinaryContainer::Read<T>() > Please use BinaryContainer::ReadString() instead for reading strings!" << std::end;
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
				std::cout << "BinaryContainer::Write<T>() > No file was opened for writing!" << endl;
				return;
			}
			if (!m_poFileStream->is_open())
			{
				cout << "BinaryContainer::Write<T>() > No file was opened for writing!" << endl;
				return;
			}

			// Check if the file was opened for writing
			if (!m_ReadWrite)
			{
				cout << "BinaryContainer::Write<T>() > File was not opened for writing!" << endl;
				return;
			}

			// Make sure the use is not trying to read a string
			if (typeid(T) == typeid(std::string))
			{
				cout << "BinaryContainer::Write<T>() > Please use BinaryContainer::ReadString() instead for reading strings!" << endl;
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