#pragma once
#include "stdafx.h"

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
		std::for_each(m_SubscribedFunctions.begin(), m_SubscribedFunctions.end(), [&](std::function<void(Args...)> f)
		{
			f(args...);
		});
	}

	void operator+=(std::function<void(Args...)> &f)
	{
		m_SubscribedFunctions.push_back(f);
	}

	void Clear()
	{
		m_SubscribedFunctions.clear();
	}

private:
	std::vector<std::function<void(Args...)>> m_SubscribedFunctions;

private:
	Event(Event const& other) = delete;
};
