#pragma region include

#include "stdafx.h"
#include "SpriteRenderComponent.h"

// game classes
#include "Game.h"
#include "GameObject.h"

#pragma endregion

SpriteRenderComponent::SpriteRenderComponent(GameObject * gameObject)
	: RenderComponent(gameObject)
{
	m_id = SPRITE_RENDER_COMPONENT;
}

SpriteRenderComponent::SpriteRenderComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: RenderComponent(gameObject, mapObject)
{
	m_id = SPRITE_RENDER_COMPONENT;
}


void SpriteRenderComponent::init(const string& path, const Vector2f& size)
{	
	Image image;

	if (!image.loadFromFile(path))
	{
		err() << "Background texture not loaded\n";
		return;
	}
	
	image.createMaskFromColor(sf::Color(255, 128, 255));

	m_texture.loadFromImage(image);
	m_texture.setSmooth(true);
	
	Vector2u texSize = m_texture.getSize();

	float scale = size.x / (float)texSize.x;
	m_gameObject->scaleObject(scale);

	m_textureSprite.setTexture(m_texture);
	auto width = m_textureSprite.getGlobalBounds().width;
	auto height = m_textureSprite.getGlobalBounds().height;
	m_textureSprite.setOrigin(Vector2f(width * 0.5f, height * 0.5f));
}

void SpriteRenderComponent::initTmxData()
{
	if (!m_mapObject)
		return;

		Vector2f size(0.f, 0.f);
		size.x = m_mapObject->width;
		size.y = m_mapObject->height;

		string path = GameObjectManager::getInstance().getAssetPath();

		for (auto property : m_mapObject->properties)
		{
			auto name = property->name;
			if (name == "Texture")
				path += property->value;
			if (name == "zIndex")
				m_zIndex = stoi(property->value);
		}

		init(path, size);

		m_mapObject = nullptr;
}

void SpriteRenderComponent::update(const float deltaTimeSeconds)
{
	Transformation gameObjCurrentTf = m_gameObject->getCurrentTf();

	m_textureSprite.setPosition(gameObjCurrentTf.getTranslation());
	m_textureSprite.setScale(gameObjCurrentTf.getScaling());
	m_textureSprite.setRotation(gameObjCurrentTf.getRotation());
}

void SpriteRenderComponent::draw(sf::RenderWindow* window)
{
	window->draw(m_textureSprite);
}

void SpriteRenderComponent::exit()
{
}

void SpriteRenderComponent::setScale(const float scale)
{
	m_textureSprite.setScale(scale, scale);
}

