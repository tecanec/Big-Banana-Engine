#include <SFML\Graphics.hpp>
#include <Windows.h>

void main()
{
#ifndef DEBUG
	FreeConsole();
#endif // DEBUG

	sf::RenderWindow window(sf::VideoMode(1600, 900), "Game");
	window.setVerticalSyncEnabled(true);

	bool gameStillGoing = true;
	while (gameStillGoing)
	{
		sf::Event polledEvent;
		while (window.pollEvent(polledEvent))
		{
			switch (polledEvent.type)
			{
			case sf::Event::Closed:
				gameStillGoing = false;
				break;
			default:
				break;
			}
		}
	}

	window.close();
}