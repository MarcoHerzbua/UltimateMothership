#pragma region include

#pragma once
#include "stdafx.h"

// abstract
#include "RenderComponent.h"

// enums
#include "GameComponents.h"

// forward declaration
class Game;
class GameObject;

using namespace std;
using namespace sf;

#pragma endregion


class ShapeRenderComponent : public RenderComponent
{
public:
	ShapeRenderComponent(GameObject* gameObject);
	ShapeRenderComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;
	void draw(RenderWindow* window) override;
	void setScale(const float scale) override;

	void initTmxData() override;

	void setColor(const Color& color);
	void setSize(const Vector2f& size);
	void setOrigin(const Vector2f& origin);

private:
	sf::RectangleShape m_shape;
};