#pragma region include

#pragma once
#include "stdafx.h"
#include "ObserverComponent.h"

using namespace std;
#pragma endregion

class ObservableComponent
{
public:
	virtual ~ObservableComponent() = default;

	void registerObserver(ObserverComponent & obs);
	void removeObserver(ObserverComponent & obs);
	void notifyObserver(string & event);
	void clearObserver();
private:
	vector<ObserverComponent*> m_observers;
};