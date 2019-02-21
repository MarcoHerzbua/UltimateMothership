#pragma region include

#pragma once
#include "stdafx.h"

#include "IGameComponent.h"

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
