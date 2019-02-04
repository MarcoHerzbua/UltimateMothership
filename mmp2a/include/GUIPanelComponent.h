#pragma region include

#pragma once
#include "stdafx.h"

// abstract
#include "IGUIWidgetComponent.h"
#include "GameEventClasses.h"

// forward declaration
class Game;
class GameObject;

#pragma endregion

class GUIPanelComponent : public IGUIWidgetComponent
{
public:
	GUIPanelComponent(GameObject* gameObject);
	GUIPanelComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTimeSeconds) override;
	void exit() override;

	void init() override;
	void initTmxData() override;

private:
};