#pragma once
#include "stdafx.h"
#include "SEObject.h"
#include "AssetDatabase.h"

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
		virtual bool Save(Content* file) = 0;
		virtual bool Save(Content* file, const std::string& path) = 0;

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

		virtual bool Save(Content* pContent) override
		{
			return StoreContent((T*)pContent);
		}

		virtual bool Save(Content* pContent, const std::string& path) override
		{
			return SaveContent((T*)pContent, path);
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
			//struct _stat buff;
			//int result = -1;
			//result = _stat(noProp.c_str(), &buff);
			//if (result != 0)
			//{
			//	std::cout << "ContentManager > File not found!\nPath: " << file << std::endl;
			//}

			T* pContent = LoadContent(file);
			return pContent;
		}

		bool StoreContent(T* pContent)
		{
			std::string path = AssetDatabase::GetAssetPath(pContent);
			return SaveContent(pContent, path);
		}

	protected:
		virtual T* LoadContent(const std::string& file) = 0;
		virtual bool SaveContent(T*, const std::string&)
		{
			throw new std::exception("Saving of this type of content is not supported!");
		}

		std::string GetFileExtension(const std::string& file)
		{
			std::filesystem::path filePath = std::filesystem::path(file);
			return filePath.extension().string();
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