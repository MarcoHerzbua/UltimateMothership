#pragma region include

#pragma once
#include "stdafx.h"

// interface
#include "IGameComponent.h"

// enums
#include "GameComponents.h"

// forward declaration
class Game;
class GameObject;

#pragma endregion

class RenderComponent : public IGameComponent
{
public:
	RenderComponent() = default;
	RenderComponent(GameObject* gameObject);
	RenderComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	virtual ~RenderComponent() = default;

	virtual void update(const float deltaTime) override = 0;
	virtual void exit() override = 0;

	virtual void draw(sf::RenderWindow* window) = 0;
	virtual void setScale(const float scale) = 0;

	virtual void initTmxData() override = 0;

	int getZIndex() { return m_zIndex; };
	void setZIndex(int idx) { m_zIndex = idx; };

protected:
	int m_zIndex = 0;
};