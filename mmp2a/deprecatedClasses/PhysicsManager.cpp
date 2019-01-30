#pragma region include

#include "stdafx.h"
#include "PhysicsManager.h"

#include "CollisionComponent.h"

#include "HelperMethods.h"


#pragma endregion


PhysicsManager& PhysicsManager::getInstance()
{
	static PhysicsManager m_instance;
	return m_instance;
}

void PhysicsManager::update(float deltaTime)
{
	handleCollisions();
}

bool PhysicsManager::AABBvsAABB(const FloatRect& a, const FloatRect& b,
	Vector2f& normal, float& penetration)
{
	Vector2f n = getCenter(b) - getCenter(a);		// Vector from A to B
	float a_extent = a.width * 0.5f;			    // Calculate half extents along x axis
	float b_extent = b.width * 0.5f;
	float x_overlap = a_extent + b_extent - abs(n.x);		// Calculate overlap on x axis
															// SAT test on x axis
	if (x_overlap > 0) {
		float a_extent = a.height * 0.5f;		// Calculate half extents along y axis
		float b_extent = b.height * 0.5f;
		float y_overlap = a_extent + b_extent - abs(n.y);	// Calculate overlap on y axis

															// SAT test on y axis
		if (y_overlap > 0) {
			// Find out which axis is axis of least penetration
			if (x_overlap < y_overlap) {
				// Point towards B knowing that n points from A to B
				if (n.x < 0)
					normal = Vector2f(1.0f, 0.0f);
				else
					normal = Vector2f(-1.0f, 0.0f);
				penetration = x_overlap;
				return true;
			}
			else {
				// Point towards B knowing that n points from A to B
				if (n.y < 0)
					normal = Vector2f(0, 1);
				else
					normal = Vector2f(0, -1);
				penetration = y_overlap;
				return true;
			}
		}
	}
	return false;
}

void PhysicsManager::findCollisions()
{
	for (auto collComp1 = m_collisionComp.begin(); collComp1 != m_collisionComp.end(); ++collComp1)
	{
		auto* body1 = (*collComp1)->getRigidBody();
		for (auto collComp2 = collComp1; collComp2 != m_collisionComp.end(); ++collComp2)
		{
			if (collComp1 == collComp2)
				continue;

			auto* body2 = (*collComp2)->getRigidBody();

			// if both object don't have a mass or body is the same skip
			if (body1->getMass() == 0 && body2->getMass() == 0)
				continue;


			Vector2f normal;
			float penetration;
			if (AABBvsAABB((*collComp1)->getShape(),
				(*collComp2)->getShape(),
				normal,
				penetration))
			{
				(*collComp1)->onCollision(body1);
				(*collComp2)->onCollision(body2);

				if (!(*collComp1)->getIsTrigger() && !(*collComp2)->getIsTrigger())
				{
					Manifold * manifold = new Manifold();
					manifold->body1 = body1;
					manifold->body2 = body2;
					manifold->normal = normal;
					manifold->penetration = penetration;

					m_manifolds.push_back(manifold);
				}
			}
		}
	}
}

void PhysicsManager::resolveCollisions()
{
	for (auto man : m_manifolds)
	{
		// Calculate relative velocity
		Vector2f rv = man->body1->getVelocity() - man->body2->getVelocity();

		// Calculate relative velocity in terms of the normal direction (length through vector projection)
		float velAlongNormal = rv.x * man->normal.x + rv.y * man->normal.y;

		// Do not resolve if velocities are separating
		if (velAlongNormal > 0)
			return;


		// Calculate impulse scalar
		const float e = 1.0f; //< 1.0 = all objects are bouncy
		float j = -(1 + e) * velAlongNormal;
		j /= man->body1->getInvMass() + man->body2->getInvMass();

		

		// Apply impulse
		float angle = (float)(rand() % 60) - 30.f;
		Vector2f randomDirectionChange = rotateVec2f(man->normal, angle * 3.1415f / 180.f);

		//std::cout << "angle: " << angle << std::endl;
		//std::cout << "x: " << man->normal.x << std::endl;
		//std::cout << "y: " << man->normal.y << std::endl;

		//std::cout << "x: " << randomDirectionChange.x << std::endl;
		//std::cout << "y: " << randomDirectionChange.y << std::endl;


		Vector2f impulse = j * randomDirectionChange;

		// impulse proportional to mass
		man->body1->addVelocity(  impulse * man->body1->getInvMass());
		man->body2->addVelocity(- impulse * man->body2->getInvMass());

		// Positional correction
		const float percent = 0.2f; // usually 20% to 80%
		const float slop = 0.01f; // usually 0.01 to 0.1
		Vector2f correction = std::max(man->penetration - slop, 0.0f) /
			(man->body1->getInvMass() + man->body2->getInvMass()) * percent * man->normal;
		// Apply directly to position
		man->body1->move(man->body1->getInvMass() * correction);
		man->body2->move(-man->body2->getInvMass() * correction);
	}
}

void PhysicsManager::handleCollisions()
{
	clearManifolds();

	findCollisions();
	resolveCollisions();
}

void PhysicsManager::addComponent(CollisionComponent * c)
{
	m_collisionComp.push_back(c);
}

void PhysicsManager::removeComponent(CollisionComponent * c)
{
	auto i = m_collisionComp.begin();

	while (i != m_collisionComp.end())
	{
		if (*i == c)
		{
			m_collisionComp.erase(i);
			return;
		}
	}

	err() << "PhysicsManager::removeComponent --- could not find component to remove" << std::endl;
}

void PhysicsManager::clearComponents()
{
	if (&m_collisionComp)
		m_collisionComp.clear();
}

void PhysicsManager::clearManifolds()
{
	for (auto& manifold : m_manifolds)
	{
		delete manifold;
	}

	m_manifolds.clear();
}