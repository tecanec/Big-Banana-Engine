#include <SFML\Graphics.hpp>
#include <Windows.h>
#include "LuaPackage.h"
#include "LuaAccess.h"
#include "ActiveObjectManager.h"

int main()
{
#ifndef DEBUG
	FreeConsole();
#endif // DEBUG

	sf::RenderWindow window(sf::VideoMode(1600, 900), "Game");
	window.setVerticalSyncEnabled(true);

	luaL_openlibs(lua::L);
	lua_register(lua::L, "makeActiveObject", AO::lAddActiveObject);
	luaL_loadstring(lua::L, R"lua(
meta = {}
function meta:Test()
	print("banana")
	print(self.text)
end

function meta:Update(number, thingytwo)
	print("This happens every frame, and my name is " .. self.name)
	print(tostring(number) .. " " .. tostring(thingytwo))
end

A = {}
A = setmetatable(A, {__index = meta})
A.text = "Hi, I am A!"
A.name = "A"
B = {}
B = setmetatable(B, {__index = meta})
B.text = "Hi, I am B!"
B.name = "B"
C = {}
C = setmetatable(C, {__index = meta})
C.text = "Hi, I am C!"
C.name = "C"

A:Test()
B:Test()
makeActiveObject(A);
makeActiveObject(B);
)lua");
	lua_call(lua::L, 0, 0);
	lua_getglobal(lua::L, "C");
	lua_pushstring(lua::L, "Test");
	lua::runMethod(-2, 0, 0);

	int thing = 0;

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

		lua_pushinteger(lua::L, thing++);
		lua_pushinteger(lua::L, thing%50);
		AO::RunMethodOnAll("Update", 2);

		window.display();
	}

	window.close();

	lua_close(lua::L);

	return 0;
}