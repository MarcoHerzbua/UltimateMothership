#pragma region include

#pragma once
#include "stdafx.h"

#include "CollisionComponent.h"
#include "RigidBodyComponent.h"

#include "HelperMethods.h"
// using
using namespace sf;
using namespace std;
using namespace hm;

#pragma endregion

struct Manifold
{
	RigidBodyComponent* body1;
	RigidBodyComponent* body2;

	float penetration;
	Vector2f normal;
};

class PhysicsManager
{
public:
	static PhysicsManager& getInstance();

	void update(float deltaTime);

	void addComponent(CollisionComponent* c);
	void removeComponent(CollisionComponent* c);

	void clearComponents();
	void clearManifolds();

private:
	PhysicsManager(void) = default;
	~PhysicsManager(void) = default;
	PhysicsManager(const PhysicsManager& p) = delete;
	PhysicsManager& operator=(PhysicsManager const&) = delete;

	bool AABBvsAABB(const FloatRect& a, const FloatRect& b,
		Vector2f& normal, float& penetration);
	void findCollisions();
	void resolveCollisions();
	void handleCollisions();


	std::vector<CollisionComponent*> m_collisionComp;

	std::vector<Manifold*> m_manifolds;
};
