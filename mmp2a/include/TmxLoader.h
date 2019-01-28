#pragma once

#include "stdafx.h"

using namespace std;
using namespace sf;

class TmxLoader
{
public:
	static void loadTmxFile(const string& path, const sf::Vector2f& offset);
};