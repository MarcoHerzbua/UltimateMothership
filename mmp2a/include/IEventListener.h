#pragma region include
#pragma once
#include "stdafx.h"

class IGameEvent;

using namespace std;
using namespace sf;

#pragma endregion

class IEventListener
{
public:
	IEventListener();
	~IEventListener();

	virtual void onEvent(IGameEvent * event) = 0;
};