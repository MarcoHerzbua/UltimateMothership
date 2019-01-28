#pragma region include

#include "stdafx.h"
#include "CameraComponent.h"

#include "IGameComponent.h"

// game classes 
#include "Game.h"
#include "GameObject.h"

#include <limits>

#pragma endregion

CameraComponent::CameraComponent(GameObject* gameObject)		
	: IGameComponent(gameObject)
{
	m_id = CAMERA_COMPONENT;
	m_window = GameObjectManager::getInstance().getGamePtr()->getWindowPtr();
}

CameraComponent::CameraComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: IGameComponent(gameObject, mapObject)
{
	m_id = CAMERA_COMPONENT;
	m_window = GameObjectManager::getInstance().getGamePtr()->getWindowPtr();
}

void CameraComponent::update(const float deltaTimeSeconds)
{
	View view = m_window->getView();
	
	Vector2f pos = m_boundObject->getCurrentTf().getTranslation();

	view.setCenter(pos);

	m_window->setView(view);
}

void CameraComponent::exit()
{
	m_window->setView(m_resetView);
}

void CameraComponent::bindCameraToObject(GameObject* boundObject)
{
	View view = m_window->getView(); 
	m_resetView = view;

	view.zoom(m_zoom);

	m_boundObject = boundObject;

	Transformation originalTf = m_boundObject->getOriginalTf();

	view.setCenter(originalTf.getTranslation());
	m_window->setView(view);
}

void CameraComponent::initTmxData()
{
	GameObject* boundObj = nullptr;
	m_zoom = 1.f;

	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name == "BoundObject")
		{
			GameObjects boundObjectId = stringToGameObjects(property->value);
			boundObj = GameObjectManager::getInstance().findGameObjects(boundObjectId)[0];
		}
		if (name == "Zoom")
		{
			m_zoom = stof(property->value);
		}
	}

	if (boundObj)
		bindCameraToObject(boundObj);
	else
		bindCameraToObject(m_gameObject);


	m_mapObject = nullptr;
}