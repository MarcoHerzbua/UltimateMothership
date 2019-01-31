#pragma region include

#include "stdafx.h"
#include "RenderManager.h"


#pragma endregion

RenderManager& RenderManager::getInstance()
{
	static RenderManager m_instance;
	return m_instance;
}

void RenderManager::draw(sf::RenderWindow* window)
{
	for (auto comp : m_components)
	{
		comp->draw(window);
	}
}

void RenderManager::sortComponents()
{
	SortRenderComp<RenderComponent>::sortByZIndex(m_components);
}

void RenderManager::addComponent(RenderComponent * c)
{
	m_components.push_back(c);

	sortComponents();
}

void RenderManager::removeComponent(RenderComponent * c)
{
	auto i = m_components.begin();

	while (i != m_components.end())
	{
		if (*i == c)
		{
			m_components.erase(i);
			return;
		}

		i++;
	}

	err() << "RenderManager::removeComponent --- could not find component to remove" << std::endl;
}

void RenderManager::clearComponents()
{
	if (&m_components)
		m_components.clear();
}
