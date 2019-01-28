#pragma region include

#pragma once
#include "stdafx.h"

// abstract
#include "RenderComponent.h"

// enums
#include "GameComponents.h"

// forward declaration
class Game;
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

private:
	Texture m_texture;
	Sprite m_textureSprite;
	
	void init(const string& path, const Vector2f& size, const Vector2f& setPos);
};