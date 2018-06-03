#pragma once

namespace AO
{
	int	lAddActiveObject(lua_State *L);

	void RunMethodOnAll(std::string method, int nargs);
}