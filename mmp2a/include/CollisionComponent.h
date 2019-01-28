#pragma once
#pragma region include

#pragma once

#include <stdafx.h>

#include "IGameComponent.h"
#include "RigidBodyComponent.h"

class Game;
class GameObject;

using namespace sf;
using namespace std;

#pragma endregion


class CollisionComponent : public IGameComponent
{
public:
	CollisionComponent(GameObject* gameObject);
	CollisionComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;
	void exit() override;

	void initTmxData() override;

	RigidBodyComponent* getRigidBody();
	FloatRect getShape();
	bool getIsTrigger();

	void addEvent(string & event);
	void onCollision(RigidBodyComponent * body);
private:
	RigidBodyComponent * m_rigidBodyComponent;
	FloatRect m_collisionShape;

	bool m_isTrigger;
	float m_triggerCooldown; //Debug Variable; prevents multiple activation of Trigger when Collision is detected
	vector<string> m_events;
};