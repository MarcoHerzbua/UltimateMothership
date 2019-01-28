#pragma region include

#pragma once

#include <stdafx.h>
#include "IGameComponent.h"
#include "ObserverComponent.h"
#include "ObservableComponent.h"

class Game;
class GameObject;

using namespace sf;
using namespace std;

#pragma endregion


class RigidBodyComponent 
	: public IGameComponent
	, public ObservableComponent
{
public:
	RigidBodyComponent(GameObject* gameObject);
	RigidBodyComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;
	void exit() override;

	void init(const float mass, const float speedLimit, const vector<Vector2f> forces);
	void initTmxData() override;

	//getter
	Vector2f getPosition();
	void move(Vector2f vec);
	Vector2f getVelocity();
	void addVelocity(Vector2f vel);
	float getMass();
	float getInvMass();
	float getSpeedlimit();

	void addImpulse(Vector2f imp);
	void clearImpulses();
	void resetVelocity();
private:
	void addForce(Vector2f force);
	void clearForces();

	float m_mass;
	float m_invMass;
	float m_speedLimit;

	vector<Vector2f> m_forces;
	vector<Vector2f> m_impulses;

	Vector2f m_acceleration;
	Vector2f m_velocity;
};