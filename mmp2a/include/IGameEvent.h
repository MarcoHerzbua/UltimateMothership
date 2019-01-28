#pragma region include

#pragma once
#include "stdafx.h"
#include "GameEvents.h"

#pragma endregion


class IGameEvent
{
public:
	IGameEvent();
	virtual ~IGameEvent() = default;
	GameEvents getID() { return m_id; };
protected:
	GameEvents m_id;
};