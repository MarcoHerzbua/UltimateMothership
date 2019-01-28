#pragma region include

#pragma once
#include "stdafx.h"

// class
#include "GameObject.h"


// stuff
#include "Transformation.h"

// enums
#include "GameComponents.h"

// forward declaration
class Game;

using namespace sf;
using namespace std;

#pragma endregion

class CameraComponent : public IGameComponent
{
public:
	CameraComponent(GameObject* gameObject);
	CameraComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTimeSeconds) override;
	void exit() override;

	void bindCameraToObject(GameObject* boundObject);
	void initTmxData() override;

	
private:
	GameObject* m_boundObject;
	RenderWindow* m_window;

	float m_zoom;

	View m_resetView;
};
