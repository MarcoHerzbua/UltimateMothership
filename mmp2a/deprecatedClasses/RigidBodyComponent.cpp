#include "stdafx.h"

#include "RigidBodyComponent.h"

// gameclasses
#include "Game.h"
#include "GameObject.h"

#include "PhysicsManager.h"


RigidBodyComponent::RigidBodyComponent(GameObject * gameObject)
	: IGameComponent(gameObject)
{
	m_id = RIGID_BODY_COMPONENT;
}

RigidBodyComponent::RigidBodyComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: IGameComponent(gameObject, mapObject)
{
	m_id = RIGID_BODY_COMPONENT;
}

void RigidBodyComponent::init(const float mass, const float speedLimit, const vector<Vector2f> forces)
{
	m_mass = mass;
	m_invMass = (mass == 0.0f) ? 0.0f : 1.f / mass;
	m_speedLimit = speedLimit;

	for (auto f : forces)
	{
		m_forces.push_back(f);
	}
}

void RigidBodyComponent::initTmxData()
{
	float mass = 0.f;
	float speedLimit = 0.f;
	vector<Vector2f> forces;

	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name == "Mass")
			mass = stof(property->value);
		if (name == "Speedlimit")
			speedLimit = stof(property->value);
		if (name.substr(0, 5) == "XForce")
			forces.push_back(Vector2f(stof(property->value), 0.f));
		if (name.substr(0, 6) == "YForce")
			forces.push_back(Vector2f(0.f, stof(property->value)));
	}

	init(mass, speedLimit, forces);


	// commented out because not in use anymore -> rigidbody is not used anyway at the moment
	/*auto object = GameObjectManager::getInstance().findGameObjects(POINT_COUNTER_OBJECT)[0];
	if (object)
	{
		auto observerComp = object->findComponents(POINT_COUNTER_COMPONENT)[0];
		registerObserver(*dynamic_cast<ObserverComponent*>(observerComp));
	}

	object = GameObjectManager::getInstance().findGameObjects(BALL_OBJECT)[0];
	if (object)
	{
		auto observerComp = object->findComponents(DEATH_ZONE_COMPONENT)[0];
		registerObserver(*dynamic_cast<ObserverComponent*>(observerComp));
	}*/
	

	m_mapObject = nullptr;
}


Vector2f RigidBodyComponent::getPosition()
{
	Transformation tf = m_gameObject->getCurrentTf();
	return tf.getTranslation();
}

Vector2f RigidBodyComponent::getVelocity()
{
	return m_velocity;
}

void RigidBodyComponent::addVelocity(Vector2f vel)
{
	m_velocity += vel;
}

float RigidBodyComponent::getMass()
{
	return m_mass;
}

float RigidBodyComponent::getInvMass()
{
	return m_invMass;
}

float RigidBodyComponent::getSpeedlimit()
{
	return m_speedLimit;
}

void RigidBodyComponent::addImpulse(Vector2f imp)
{
	m_impulses.push_back(imp);
}

void RigidBodyComponent::clearImpulses()
{
	m_impulses.clear();
}

void RigidBodyComponent::addForce(Vector2f force)
{
	m_forces.push_back(force);
}

void RigidBodyComponent::clearForces()
{
	m_forces.clear();
}

void RigidBodyComponent::update(float deltaTime)
{
	Vector2f forces{};
	// forces are constantly applied to body
	for (const auto& f : m_forces)
		forces += f;

	// impulses are applied only once
	for (const auto& i : m_impulses)
		forces += i;

	clearImpulses();

	// symplectic Euler
	m_acceleration = forces * m_invMass;
	m_velocity += m_acceleration * deltaTime;

	const float squaredSpeedLimit = m_speedLimit * m_speedLimit;

	auto length2 = [](const Vector2f &vec) -> float { return vec.x * vec.x + vec.y * vec.y; };
	auto adjustLength = [length2](const Vector2f &vec, const float length) -> Vector2f { return (vec / sqrt(length2(vec))) * length; };

	if (length2(m_velocity) > squaredSpeedLimit)
	{
		m_velocity = adjustLength(m_velocity, m_speedLimit);
	}

	//m_velocity = m_velocity * 0.999f; //< simple "friction"

	move(m_velocity * deltaTime);
}

void RigidBodyComponent::resetVelocity()
{
	m_velocity = Vector2f(0.f, 0.f);
}

void RigidBodyComponent::move(Vector2f vec)
{
	m_gameObject->moveObject(vec);
}

void RigidBodyComponent::exit()
{
	clearImpulses();
	clearForces();
	clearObserver();
}


