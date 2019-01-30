#include "stdafx.h"

#include "CollisionComponent.h"

// gameclasses
#include "Game.h"
#include "GameObject.h"

#include "PhysicsManager.h"

CollisionComponent::CollisionComponent(GameObject * gameObject)
	: IGameComponent(gameObject)
{
	m_id = COLLISION_COMPONENT;
	PhysicsManager::getInstance().addComponent(this);
}

CollisionComponent::CollisionComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: IGameComponent(gameObject, mapObject)
{
	m_id = COLLISION_COMPONENT;
	PhysicsManager::getInstance().addComponent(this);
}

void CollisionComponent::initTmxData()
{
	auto rigidBody = m_gameObject->findComponents(RIGID_BODY_COMPONENT)[0];

	//check if cast was successful, nullptr if cast failed
	if (!rigidBody)
	{
		err() << "could not initialize CollisionComponent; no RigidBodyComponent found";
		return;
	}

	m_rigidBodyComponent = dynamic_cast<RigidBodyComponent*>(rigidBody);

	Vector2f shapeSize = Vector2f(m_mapObject->width, m_mapObject->height);
	Vector2f shapePos = m_rigidBodyComponent->getPosition();

	m_collisionShape = FloatRect(shapePos, shapeSize);

	m_isTrigger = false;

	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name == "Trigger")
			if (property->value == "true")
				m_isTrigger = true;
		if (name.substr(0, 5) == "Event")
			addEvent(property->value);
	}

	m_mapObject = nullptr;
}

void CollisionComponent::update(const float deltaTime)
{
	if (m_triggerCooldown > 0.f)
	{
		m_triggerCooldown -= deltaTime;
		if (m_triggerCooldown <= 0.f)
			m_triggerCooldown = 0;
	}

	Vector2f tf = m_gameObject->getCurrentTf().getTranslation();
	m_collisionShape.top = tf.y;
	m_collisionShape.left = tf.x;

	auto rotateFloatRect = [](const FloatRect &rect, float angle) -> FloatRect 
	{ 
		RectangleShape rectShape = RectangleShape(Vector2f(rect.width, rect.height));
		rectShape.setPosition(Vector2f(rect.left, rect.top));

		angle = ((int)angle / 90) * 90.f;
		
		rectShape.setRotation(angle);

		FloatRect newRect = rectShape.getGlobalBounds();
	
		return newRect;
	};

	m_collisionShape = rotateFloatRect(m_collisionShape, m_gameObject->getCurrentTf().getRotation());
}

void CollisionComponent::exit()
{
	m_events.clear();
}

RigidBodyComponent* CollisionComponent::getRigidBody()
{
	return m_rigidBodyComponent;
}

FloatRect CollisionComponent::getShape()
{
	return m_collisionShape;
}

bool CollisionComponent::getIsTrigger()
{
	return m_isTrigger;
}

void CollisionComponent::addEvent(string & event)
{
	m_events.push_back(event);
}

void CollisionComponent::onCollision(RigidBodyComponent * body)
{
	if (!m_isTrigger || m_triggerCooldown != 0)
		return;
	
	m_triggerCooldown = 1.f;
	for (auto ev : m_events)
	{
		m_rigidBodyComponent->notifyObserver(ev);
	}
}

