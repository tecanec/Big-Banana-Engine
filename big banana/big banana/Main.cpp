#include <SFML\Graphics.hpp>
#include <Windows.h>

void main()
{
#ifndef DEBUG
	FreeConsole();
#endif // DEBUG

	sf::RenderWindow window(sf::VideoMode(1600, 900), "Game");
}