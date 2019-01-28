#include "stdafx.h"
#include "ObservableComponent.h"

void ObservableComponent::registerObserver(ObserverComponent & obs)
{
	m_observers.push_back(&obs);
}

void ObservableComponent::removeObserver(ObserverComponent & obs)
{
	//TODO: Implement removeObserver
}
void ObservableComponent::notifyObserver(string & event)
{
	for (auto obs : m_observers)
	{
		obs->onNotification(event);
	}
}
void ObservableComponent::clearObserver()
{
	m_observers.clear();
}
