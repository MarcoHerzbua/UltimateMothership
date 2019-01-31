#pragma region include

#include "stdafx.h"
#include "ShapeRenderComponent.h"

// game classes
#include "Game.h"
#include "GameObject.h"

#pragma endregion

ShapeRenderComponent::ShapeRenderComponent(GameObject * gameObject)
	: RenderComponent(gameObject)
{
	m_id = SHAPE_RENDER_COMPONENT;
}

ShapeRenderComponent::ShapeRenderComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: RenderComponent(gameObject, mapObject)
{
	m_id = SHAPE_RENDER_COMPONENT;
}

void ShapeRenderComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name == "zIndex")
			m_zIndex = stoi(property->value);
	}

	Vector2f size(m_mapObject->width, m_mapObject->height);
	m_shape = RectangleShape(size);
	m_shape.setFillColor(Color(128, 0, 255)); //TODO change to color from tiled

	m_mapObject = nullptr;
}

void ShapeRenderComponent::update(const float deltaTimeSeconds)
{
	Transformation gameObjCurrentTf = m_gameObject->getCurrentTf();

	m_shape.setPosition(gameObjCurrentTf.getTranslation());
	m_shape.setScale(gameObjCurrentTf.getScaling());
	m_shape.setRotation(gameObjCurrentTf.getRotation());
}

void ShapeRenderComponent::draw(RenderWindow* window)
{
	window->draw(m_shape);
}


void ShapeRenderComponent::setScale(const float scale)
{
	m_shape.setScale(scale, scale);
}


void ShapeRenderComponent::setColor(const Color& color)
{
	m_shape.setFillColor(color);
	m_shape.setOutlineColor(color);
}

void ShapeRenderComponent::setSize(const Vector2f& size)
{
	m_shape.setSize(size);
}

void ShapeRenderComponent::setOrigin(const Vector2f& origin)
{
	m_shape.setOrigin(origin);
}