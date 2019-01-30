#pragma region include

#include "stdafx.h"
#include "DeathZoneComponent.h"
#include "PhysicsManager.h"

// gameclasses
#include "Game.h"
#include "GameObject.h"

#pragma endregion

DeathZoneComponent::DeathZoneComponent(GameObject * gameObject)
	: IGameComponent(gameObject)
{
	m_id = DEATH_ZONE_COMPONENT;
}

DeathZoneComponent::DeathZoneComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: IGameComponent(gameObject, mapObject)
{
	m_id = DEATH_ZONE_COMPONENT;
}

void DeathZoneComponent::update(const float deltaTimeSeconds)
{

}

void DeathZoneComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	m_mapObject = nullptr;
}

void DeathZoneComponent::onNotification(string & event)
{
	if (event == "Death")
	{		
		Transformation tf = m_gameObject->getOriginalTf();
		m_gameObject->moveObject(-m_gameObject->getCurrentTf().getTranslation());
		m_gameObject->moveObject(tf.getTranslation());

		m_gameObject->scaleObject(tf.getScaling());
		m_gameObject->rotateObject(tf.getRotation());

		auto rigidBody = dynamic_cast<RigidBodyComponent*>(m_gameObject->findComponents(RIGID_BODY_COMPONENT)[0]);
		rigidBody->clearImpulses();
		rigidBody->resetVelocity();
	}
}

void DeathZoneComponent::exit()
{

}
