#pragma region include 

#pragma once
#include "stdafx.h"
#include "IGameEvent.h"


class IEventListener;
#pragma endregion

class Eventbus
{
public:
	static Eventbus& getInstance();

	void update();
	
	void registerListener(IEventListener * listener);
	std::vector<IEventListener *>::iterator findListenerIterator(const IEventListener * listener);
	void removeListener(const IEventListener * listener);

	void notifyListeners(IGameEvent * event);

	void fireEvent(IGameEvent * event);
private:
	Eventbus() = default;
	~Eventbus() = default;
	Eventbus(const Eventbus &e) = delete;
	Eventbus& operator= (Eventbus const&) = delete;

	std::queue<IGameEvent *> m_events_0;
	std::queue<IGameEvent *> m_events_1;
	std::vector<IEventListener *> m_listeners;
};