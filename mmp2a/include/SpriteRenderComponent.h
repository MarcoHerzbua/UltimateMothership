#pragma region include

#pragma once
#include "stdafx.h"

// abstract
#include "RenderComponent.h"

class GameObject;

using namespace sf;
using namespace std;
#pragma endregion


class SpriteRenderComponent : public RenderComponent
{
public:
	SpriteRenderComponent(GameObject* gameObject);
	SpriteRenderComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;
	void draw(RenderWindow* window) override;
	void exit() override;
	void setScale(const float scale) override;

	void initTmxData() override;

	void activate() { m_active = true; };
	void deactivate() { m_active = false; };

private:
	Texture m_texture;
	Sprite m_textureSprite;
	bool m_active = true;
	int m_setId = 0;
	
	void init(const string& path, const Vector2f& size, const Vector2f& setPos);
};