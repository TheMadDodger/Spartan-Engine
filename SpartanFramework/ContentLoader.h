#pragma once
#include "stdafx.h"
#include "SEObject.h"

namespace Spartan
{
	class BaseLoader
	{
	public:
		BaseLoader(const std::vector<std::string>& fileExtensions) : m_FileExtensions(fileExtensions) {}
		virtual ~BaseLoader() {}

		virtual const std::type_info& GetType() = 0;
		bool HasExtension(const std::string& extension)
		{
			auto it = std::find(m_FileExtensions.begin(), m_FileExtensions.end(), extension);
			return (it != m_FileExtensions.end());
		}

		virtual Content* Load(const std::string& file) = 0;

	private:
		BaseLoader(const BaseLoader& obj) = delete;
		BaseLoader& operator=(const BaseLoader& obj) = delete;

		const std::vector<std::string> m_FileExtensions;
	};

	template <class T>
	class ContentLoader : public BaseLoader
	{
	public:
		ContentLoader(const std::vector<std::string>& fileExtensions) : BaseLoader(fileExtensions)
		{
			++m_Loaders;
		}
		virtual ~ContentLoader()
		{
			--m_Loaders;
		}

		virtual const type_info& GetType() override { return typeid(T); };

		virtual Content* Load(const std::string& file) override
		{
			T* pContent = GetContent(file);
			return (Content*)pContent;
		}

		T* GetContent(const std::string& file)
		{
			// Remove properties at end
			auto index = file.find(':');
			auto noProp = file;
			if (index != std::string::npos)
			{
				noProp = noProp.substr(0, index);
			}

			//Does File Exists?
			struct _stat buff;
			int result = -1;
			result = _stat(noProp.c_str(), &buff);
			if (result != 0)
			{
				std::cout << "ContentManager > File not found!\nPath: " << file << std::endl;
			}

			T* pContent = LoadContent(file);
			return pContent;
		}

	protected:
		virtual T* LoadContent(const std::string& file) = 0;

		std::string GetFileExtension(const std::string& file)
		{
			int dotIndex = file.rfind('.') + 1;
			return file.substr(dotIndex);
		}

	private:
		static int m_Loaders;

	private:
		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		ContentLoader(const ContentLoader& obj);
		ContentLoader& operator=(const ContentLoader& obj);
	};

	template <class T>
	int ContentLoader<T>::m_Loaders = 0;
}