#include "stdafx.h"
#include "HelperMethods.h"

#include "GameObject.h"
#include "ShipComponent.h"
#include "Node.h"


float hm::calcNodeDistance(Node& a, Node& b)
{
	Vector2f pos = a.getPosition() - b.getPosition();
	return sqrt(pos.x * pos.x + pos.y * pos.y);
}

Vector2f hm::calcDistVec(Node& a, Node& b)
{
	Vector2f pos = a.getPosition() - b.getPosition();

	return pos;
}

Vector2f hm::normalizeVec2f(Vector2f vec)
{
	float vecLength = std::sqrt(vec.x * vec.x + vec.y * vec.y);
	return vec / vecLength;
}

Vector2f hm::rotateVec2f(const Vector2f & vec, const float angle)
{
	Vector2f newVec;

	newVec.x = vec.x * cos(angle) - vec.y * sin(angle);
	newVec.y = vec.x * sin(angle) + vec.y * cos(angle);

	return newVec;
}

Vector2f hm::getCenter(const FloatRect & rect)
{
	return Vector2f(rect.left, rect.top) + 0.5f * Vector2f(rect.width, rect.height);
}

ShipComponent* hm::getShipFromGameObject(GameObject* g)
{
	ShipComponent* ship;

	auto s = g->findComponents(FIGHTER_SHIP_COMPONENT);
	if (s.size() > 0)
		ship = static_cast<ShipComponent*>(s[0]);
	else
	{
		s = g->findComponents(MOTHER_SHIP_COMPONENT);
		if (s.size() > 0)
			ship = static_cast<ShipComponent*>(s[0]);
		else
		{
			s = g->findComponents(FARM_SHIP_COMPONENT);
			if (s.size() > 0)
				ship = static_cast<ShipComponent*>(s[0]);
			else
				return nullptr;
		}
	}

	return ship;
}