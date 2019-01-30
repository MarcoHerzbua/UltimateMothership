#pragma once
#include "stdafx.h"

#include "Node.h"

class GameObject;
class ShipComponent;

using namespace std;
using namespace sf;

namespace hm
{

	template<typename T>
	struct SortRenderComp
	{
		bool operator()(T * lhs, T * rhs) const
		{
			return lhs->getZIndex() < rhs->getZIndex();
		}

		static void sortByZIndex(vector<T*>& vec)
		{
			sort(vec.begin(), vec.end(), SortRenderComp<T>());
		}
	};

	float calcNodeDistance(Node& a, Node& b);
	Vector2f calcDistVec(Node& a, Node& b);

	Vector2f normalizeVec2f(Vector2f vec);
	Vector2f rotateVec2f(const Vector2f &vec, const float angle);
	
	Vector2f getCenter(const FloatRect& rect);
	
	ShipComponent* getShipFromGameObject(GameObject* g);
}
