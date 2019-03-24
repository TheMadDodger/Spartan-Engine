#pragma once

template<typename T>
class Singleton
{
public:
	static T *GetInstance()
	{
		if (!m_pInstance) m_pInstance = new T();
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

private:
	static T *m_pInstance;
};

template<typename T>
T * Singleton<T>::m_pInstance = nullptr;
