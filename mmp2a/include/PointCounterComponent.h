#pragma region include

#pragma once
#include "stdafx.h"

#include "ObserverComponent.h"
#include "IGameComponent.h"

// enums
#include "GameComponents.h"

// forward declaration
class Game;
class GameObject;

#pragma endregion

class PointCounterComponent 
	: public IGameComponent
	, public ObserverComponent
{
public:
	PointCounterComponent(GameObject* gameObject);
	PointCounterComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTimeSeconds) override;
	void exit() override;

	void onNotification(string & event) override;

	void initTmxData() override;

	void displayCount();

private:
	int m_counter;
};