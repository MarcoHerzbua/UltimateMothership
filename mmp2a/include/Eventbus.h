#pragma region include 

#pragma once
#include "stdafx.h"

class IEventListener;
class IGameEvent;

using namespace std;
using namespace sf;
#pragma endregion

class Eventbus
{
public:
	static Eventbus& getInstance();

	void update();
	
	void registerListener(IEventListener * listener);
	vector<IEventListener *>::iterator findListenerIterator(const IEventListener * listener);
	void removeListener(const IEventListener * listener);

	void notifyListeners(IGameEvent * event);

	void fireEvent(IGameEvent * event);
private:
	Eventbus() = default;
	~Eventbus() = default;
	Eventbus(const Eventbus &e) = delete;
	Eventbus& operator= (Eventbus const&) = delete;

	queue<IGameEvent *> m_events_0;
	queue<IGameEvent *> m_events_1;
	queue<IGameEvent *> * m_activeQueue = &m_events_0;
	vector<IEventListener *> m_listeners;
};