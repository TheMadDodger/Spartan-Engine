#pragma once
#include "../../stdafx.h"

class BaseLoader
{
public:
	BaseLoader() {}
	virtual ~BaseLoader() {}

	virtual const type_info& GetType() const = 0;
	virtual void Unload() = 0;

private:
	BaseLoader(const BaseLoader &obj) = delete;
	BaseLoader& operator=(const BaseLoader& obj) = delete;
};

template <class T>
class ContentLoader : public BaseLoader
{
public:
	ContentLoader()
	{
		++m_Loaders;
	}
	virtual ~ContentLoader()
	{
		--m_Loaders;
	}

	virtual const type_info& GetType() const { return typeid(T); };

	T* GetContent(const std::string &file)
	{
		// Remove properties at end
		auto index = file.find(':');
		auto noProp = file;
		if (index != string::npos)
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

	void Unload()
	{

	}

protected:
	virtual T* LoadContent(const std::string& file) = 0;

private:
	static int m_Loaders;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	ContentLoader(const ContentLoader &obj);
	ContentLoader& operator=(const ContentLoader& obj);
};

template <class T>
int ContentLoader<T>::m_Loaders = 0;