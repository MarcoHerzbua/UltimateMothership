#include "stdafx.h"
#include "Eventbus.h"

#include "IEventListener.h"
#include "IGameEvent.h"

Eventbus & Eventbus::getInstance()
{
	static Eventbus m_instance;
	return m_instance;
}

void Eventbus::update()
{
	while (m_activeQueue->size() != 0)
	{
		IGameEvent * event = m_activeQueue->front();
		notifyListeners(event);
		delete event;
		m_activeQueue->pop();
	}
	if (m_activeQueue == &m_events_0)
		m_activeQueue = &m_events_1;
	else
		m_activeQueue = &m_events_0;
}

void Eventbus::registerListener(IEventListener * listener)
{
	//m_listeners.push_back(listener);
	m_listeners.insert(m_listeners.begin(), listener);
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

	if (lIt != m_listeners.end())
	{
		(*lIt) = nullptr;
		//m_listeners.erase(lIt);
	}
}

void Eventbus::notifyListeners(IGameEvent * event)
{
	for (auto *l : m_listeners)
	{
		//TODO: rework to properly remove listeners from m_listeners
		if (l)
			l->onEvent(event);
		else
			m_listeners.erase(findListenerIterator(l));
	}

}

void Eventbus::fireEvent(IGameEvent *event)
{
	m_activeQueue->push(event);
}
