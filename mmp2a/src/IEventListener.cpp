#include "stdafx.h"
#include "IEventListener.h"

#include "Eventbus.h"

IEventListener::IEventListener()
{
	Eventbus::getInstance().registerListener(this);
}

IEventListener::~IEventListener()
{
	Eventbus::getInstance().removeListener(this);
}
