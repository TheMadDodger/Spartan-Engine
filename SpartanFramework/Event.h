#pragma once
#include "stdafx.h"

namespace Spartan
{
	template<typename ...Args>
	struct Event
	{
	public:
		Event() {};
		virtual ~Event()
		{
			m_SubscribedFunctions.clear();
		}

		void operator()(Args... args)
		{
			std::for_each(m_SubscriptionNames.begin(), m_SubscriptionNames.end(), [&](const std::string& name)
			{
				auto f = m_SubscribedFunctions.at(name);
				f(args...);
			});
		}

		void Subscribe(const std::string& name, std::function<void(Args...)>& f)
		{
			auto it = m_SubscribedFunctions.find(name);
			if (it != m_SubscribedFunctions.end()) return;
			m_SubscribedFunctions[name] = f;
			m_SubscriptionNames.push_back(name);
		}

		void Unsubscribe(const std::string& name)
		{
			auto it = m_SubscribedFunctions.find(name);
			if (it == m_SubscribedFunctions.end()) return;
			m_SubscribedFunctions.erase(name);
			m_SubscriptionNames.remove(name);
		}

		void Clear()
		{
			m_SubscribedFunctions.clear();
		}

	private:
		std::map<std::string, std::function<void(Args...)>> m_SubscribedFunctions;
		std::list<std::string> m_SubscriptionNames;

	private:
		Event(Event const& other) = delete;
	};
}