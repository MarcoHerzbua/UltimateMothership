#pragma region include

#include "stdafx.h"
#include "PointCounterComponent.h"

// gameclasses
#include "Game.h"
#include "GameObject.h"

#pragma endregion

PointCounterComponent::PointCounterComponent(GameObject * gameObject)
	: IGameComponent(gameObject)
{
	m_id = POINT_COUNTER_COMPONENT;
}

PointCounterComponent::PointCounterComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: IGameComponent(gameObject, mapObject)
{
	m_id = POINT_COUNTER_COMPONENT;
}

void PointCounterComponent::update(const float deltaTimeSeconds)
{

}

void PointCounterComponent::initTmxData()
{
	m_counter = 0;

	if (!m_mapObject)
		return;

	m_mapObject = nullptr;
}

void PointCounterComponent::onNotification(string & event)
{
	if (event == "AddPoints")
	{
		m_counter++;
		displayCount();
	}
	if (event == "Death")
	{
		m_counter = 0;
		displayCount();
	}
}

void PointCounterComponent::displayCount()
{
	cout << "Points: " << m_counter << endl;
}

void PointCounterComponent::exit()
{

}
