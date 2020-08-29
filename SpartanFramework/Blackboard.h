#pragma once
#include "SEObject.h"

namespace Spartan
{
	class BlackboardValueBase
	{
	public:
		explicit BlackboardValueBase() {}
		virtual ~BlackboardValueBase() {}
	};

	template<typename T>
	class BlackboardValue : public BlackboardValueBase
	{
	public:
		BlackboardValue(T value) : Data(value) {}
		T Data;
	};

	class Blackboard
	{
	public:
		Blackboard() {};
		~Blackboard()
		{
			map<std::string, BlackboardValueBase*>::iterator it;
			for (it = m_pValues.begin(); it != m_pValues.end(); ++it)
			{
				delete it->second;
			}
			m_pValues.clear();
		}

		template<typename T>
		void Add(T value, const std::string& name)
		{
			auto pValue = new BlackboardValue<T>(value);
			m_pValues[name] = pValue;
		}

		template<typename T>
		bool Get(const std::string& name, T& data)
		{
			if (m_pValues.count(name) <= 0)
				return false;

			auto pValue = dynamic_cast<BlackboardValue<T>*>(m_pValues[name]);
			if (pValue)
			{
				data = pValue->Data;
				return true;
			}
			return false;
		}

		template<typename T>
		void Set(T value, const std::string& name)
		{
			if (m_pValues.count(name) <= 0)
				return;

			auto pValue = dynamic_cast<BlackboardValue<T>*>(m_pValues[name]);
			if (pValue)
			{
				pValue->Data = value;
			}
		}

	private:
		std::map<std::string, BlackboardValueBase*> m_pValues;
	};
}