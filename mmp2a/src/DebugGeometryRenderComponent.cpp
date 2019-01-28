#pragma region include

#include "stdafx.h"
#include "DebugGeometryRenderComponent.h"

// game classes
#include "Game.h"
#include "GameObject.h"

#pragma endregion

DebugGeometryRenderComponent::DebugGeometryRenderComponent(GameObject * gameObject)
	: RenderComponent(gameObject)
{
	m_id = DEBUG_GEOMETRY_RENDER_COMPONENT;
}

DebugGeometryRenderComponent::DebugGeometryRenderComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: RenderComponent(gameObject, mapObject)
{
	m_id = DEBUG_GEOMETRY_RENDER_COMPONENT;
}

void DebugGeometryRenderComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	Vector2f shapeSize = Vector2f(m_mapObject->width, m_mapObject->height);

	m_debugShape = RectangleShape(shapeSize);
	m_debugShape.setFillColor(Color::Transparent);
	m_debugShape.setOutlineColor(Color::Red);
	m_debugShape.setOutlineThickness(1);

	m_mapObject = nullptr;
}

void DebugGeometryRenderComponent::update(const float deltaTimeSeconds)
{
	m_debugShape.setPosition(m_gameObject->getCurrentTf().getTranslation());
	m_debugShape.setRotation(m_gameObject->getCurrentTf().getRotation());
}

void DebugGeometryRenderComponent::draw(RenderWindow* window)
{
	window->draw(m_debugShape);
}

void DebugGeometryRenderComponent::exit()
{

}
