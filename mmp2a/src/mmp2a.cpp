// Main entrypoint of the application
// Creates a Game object and Runs it

#pragma region include

#include "stdafx.h"
#include "Game.h"

#pragma endregion

int main(int argc, char * argv[])
{
	Game game;

	if (argc == 3)
	{
		const string windowWidth_str = argv[1];
		const string windowHeight_str = argv[2];

		const int windowWidth = stoi(windowWidth_str);
		const int windowHeight = stoi(windowHeight_str);

		game.setWindowSize(Vector2u(windowWidth, windowHeight));
	}
		
	game.run();
	return 0;
}

