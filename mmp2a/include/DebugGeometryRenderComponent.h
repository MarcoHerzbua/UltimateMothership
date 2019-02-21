#pragma region include

#pragma once
#include "stdafx.h"

#include "RenderComponent.h"

using namespace sf;
using namespace std;
#pragma endregion


class DebugGeometryRenderComponent : public RenderComponent
{
public:
	DebugGeometryRenderComponent(GameObject* gameObject);
	DebugGeometryRenderComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void initTmxData() override;


	virtual void update(const float deltaTimeSeconds) override;
	virtual void draw(RenderWindow* window) override;

	virtual void setScale(const float scale) override {};

	//void setColor(sf::Color color);
	//void setSize(sf::Vector2f size);
	//void setOrigin(sf::Vector2f origin);

private:
	RectangleShape m_debugShape;
	//RigidBodyComponent * m_rigidBodyComp;
};