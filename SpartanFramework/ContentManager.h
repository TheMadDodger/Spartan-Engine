#pragma once
#include "ContentLoader.h"
#include "MathHelpers.h"
#include "Debug.h"
#include "SEObject.h"
#include "Manager.h"
#include "VertexHelpers.h"
#include "Content.h"
#include "Gradient.h"

namespace Spartan
{
#pragma warning(disable:4996)
	class ContentManager : Manager
	{
	public: // Singleton calls
		static ContentManager* GetInstance();
		static void Destroy();

	public: // System methods
		void Initialize();

		template <typename T>
		T* Load(std::string file)
		{
			//for (Content* pContent : m_pContent)
			//{
			//	if (pContent->m_FileName == file)
			//		return static_cast<T*>(pContent);
			//}

			for (BaseLoader* pLoader : m_pLoaders)
			{
				const type_info& ti = typeid(T);
				if (pLoader->GetType() == ti)
				{
					T* pContent = static_cast<ContentLoader<T>*>(pLoader)->GetContent(file);
					if (pContent != nullptr)
					{
						m_pContent.push_back(pContent);
						return pContent;
					}
				}
			}

			return nullptr;
		}

		static bool FileExists(const std::string& file)
		{
			if (FILE* f = fopen(file.c_str(), "r")) {
				fclose(f);
				return true;
			}
			else {
				return false;
			}
		}

	private:
		void AddLoader(BaseLoader* pLoader);

	private: // Content data
		std::vector<Content*> m_pContent;
		std::vector<BaseLoader*> m_pLoaders;

	private: // Singleton
		ContentManager();
		~ContentManager();
		static ContentManager* m_pContentManager;
	};
}