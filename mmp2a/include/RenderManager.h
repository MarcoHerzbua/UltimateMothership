#pragma region include

#pragma once
#include "stdafx.h"

#include "RenderComponent.h"

#include "HelperMethods.h"

using namespace sf;
using namespace hm;
using namespace std;

#pragma endregion


class RenderManager
{
public:
	static RenderManager& getInstance();

	void draw(sf::RenderWindow* window);

	void addComponent(RenderComponent* c);
	void removeComponent(RenderComponent* c);

	void clearComponents();
	void sortComponents();

private:
	RenderManager(void) = default;
	~RenderManager(void) = default;
	RenderManager(const RenderManager& p) = delete;
	RenderManager& operator=(RenderManager const&) = delete;
	
	std::vector<RenderComponent*> m_components;
	tgui::Gui m_gui;
};
