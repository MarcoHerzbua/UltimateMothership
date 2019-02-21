#pragma region include

#include "stdafx.h"
#include "GameObject.h"

#include "IGameComponent.h"

#include "GameObjectManager.h"

#pragma endregion

GameObject::GameObject(const GameObjects id)
	: GameObject(id, Transformation())
{
}

GameObject::GameObject(const GameObjects id, const Transformation transform)
{
	m_originalTransformation = transform;

	moveObject(m_originalTransformation.getTranslation());
	scaleObject(m_originalTransformation.getScaling());
	rotateObject(m_originalTransformation.getRotation());

	m_id = id;

	GameObjectManager::getInstance().registerGameObject(this);
}

void GameObject::update(const float deltaTimeSeconds)
{
	m_velocity = Vector2f(0.0f, 0.0f);

	for (auto& component : m_components)
	{
		component->update(deltaTimeSeconds);
	}

	moveObject(m_velocity);
}

void GameObject::exit()
{
	for (auto& component : m_components)
	{
		component->exit();
		delete component;
	}

	m_components.clear();
}

void GameObject::moveObject(const sf::Vector2f move)
{
	m_currentTransformation.moveTf(move);
	this->translate(move);
}

void GameObject::setPosition(const sf::Vector2f & pos)
{
	m_currentTransformation.setPosition(pos);
}

void GameObject::scaleObject(const float scale)
{
	m_currentTransformation.scaleTf(scale);
	this->scale(scale, scale);
}
void GameObject::scaleObject(const sf::Vector2f scale)
{
	m_currentTransformation.scaleTf(scale);
	this->scale(scale);
}

void GameObject::rotateObject(const float angle)
{
	m_currentTransformation.rotateTf(angle);
	this->rotate(angle);
}

void GameObject::initTmxData()
{
	for (auto component : m_components)
	{
		component->initTmxData();
	}
}

void GameObject::addComponent(IGameComponent* c)
{
	m_components.push_back(c);
}

void GameObject::addComponents(vector<IGameComponent*> cv)
{
	for (auto c : cv)
		m_components.push_back(c);
}

void GameObject::removeComponent(IGameComponent* c)
{
	auto cIti = findFirstComponentIterator(c);
	if (cIti != m_components.end())
	{
		m_components.erase(cIti);

		(*cIti)->exit();
		delete *cIti;
	}
}

void GameObject::removeComponents(const GameComponents cId)
{
	auto cIti = findFirstComponentIterator(cId);
	while (cIti != m_components.end())
	{
		m_components.erase(cIti);

		(*cIti)->exit();
		delete *cIti;

		cIti = findFirstComponentIterator(cId);
	}
}

void GameObject::clearComponents()
{
	for (auto c : m_components)
	{
		c->exit();
		delete c;
	}

	m_components.clear();
}

vector<IGameComponent*> GameObject::findComponents(const GameComponents cId)
{
	vector<IGameComponent*> components;

	for (auto c : m_components)
	{
		if (c->getId() == cId)
			components.push_back(c);
	}

	return components;
}

vector<IGameComponent*>::iterator GameObject::findFirstComponentIterator(const GameComponents cId)
{
	for (auto cIti = m_components.begin(); cIti != m_components.end(); cIti++)
	{
		if ((*cIti)->getId() == cId) return cIti;
	}

	return m_components.end();
}

vector<IGameComponent*>::iterator GameObject::findFirstComponentIterator(IGameComponent* c)
{
	for (auto cIti = m_components.begin(); cIti != m_components.end(); cIti++)
	{
		if ((*cIti) == c) return cIti;
	}

	return m_components.end();
}
