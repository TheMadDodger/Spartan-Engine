#pragma once
#include "SEObject.h"

namespace SpartanEngine
{
	template<typename T>
	class Singleton : Manager
	{
	public:
		static T* GetInstance()
		{
			if (!m_pInstance)
			{
				m_pInstance = new T();
				m_pInstance->OnInstanceCreated();
			}
			return m_pInstance;
		}

		static void Destroy()
		{
			if (m_pInstance)
			{
				delete m_pInstance;
				m_pInstance = nullptr;
			}
		}

	protected:
		virtual void OnInstanceCreated() {}

	private:
		static T* m_pInstance;
	};

	template<typename T>
	T* Singleton<T>::m_pInstance = nullptr;
}