#include "stdafx.h"
#include "Eventbus.h"
#include "IEventListener.h"


Eventbus & Eventbus::getInstance()
{
	static Eventbus m_instance;
	return m_instance;
}

void Eventbus::update()
{
	while (m_events_0.size() != 0)
	{
		IGameEvent * event = m_events_0.front();
		notifyListeners(event);
		m_events_0.pop();
	}
}

void Eventbus::registerListener(IEventListener * listener)
{
	m_listeners.push_back(listener);
}

std::vector<IEventListener*>::iterator Eventbus::findListenerIterator(const IEventListener * listener)
{
	for (auto it = m_listeners.begin(); it != m_listeners.end(); it++)
	{
		if ((*it) == listener)
			return it;
	}

	return m_listeners.end();
}

void Eventbus::removeListener(const IEventListener * listener)
{
	auto lIt = findListenerIterator(listener);

	if(lIt == m_listeners.end())
		m_listeners.erase(lIt);
}

void Eventbus::notifyListeners(IGameEvent * event)
{
	for (auto *l : m_listeners)
	{
		l->onEvent(event);
	}
}

void Eventbus::fireEvent(IGameEvent *event)
{
	m_events_0.push(event);
}
