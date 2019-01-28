#pragma region include
#pragma once
#include "stdafx.h"
#include "IGameEvent.h"
#include "Eventbus.h"
#pragma endregion

class IEventListener
{
public:
	IEventListener();
	~IEventListener();

	virtual void onEvent(IGameEvent * event) = 0;
};