#include "LuaPackage.h"
#include "LuaAccess.h"
#include <string>
#include "ActiveObjectManager.h"
#include <unordered_set>


lua::LuaObject AOSet;
std::unordered_set<int> keys = {};


int AO::lAddActiveObject(lua_State *L)
{
	if (!AOSet.HasValue())
	{
		lua_createtable(L, 1, 0);
		AOSet.Set();
	}

	AOSet.Get();
	lua_insert(L, -2);
	keys.insert(luaL_ref(L, -2));
	lua_pop(L, 1);

	return 0;
}


void AO::RunMethodOnAll(std::string method, int nargs)
{
	if (!AOSet.HasValue())
		return;

	int argsStart = lua_absindex(lua::L, -nargs);

	AOSet.Get();

	for (std::unordered_set<int>::iterator i = keys.begin(); i != keys.end(); ++i)
	{
		int key = *i;
		lua_pushinteger(lua::L, key);
		lua_gettable(lua::L, -2);

		lua_pushstring(lua::L, method.c_str());
		lua_gettable(lua::L, -2);
		lua_insert(lua::L, -2);

		for (int j = argsStart; j < argsStart + nargs; j++)
		{
			lua_pushvalue(lua::L, j);
		}

		lua_call(lua::L, nargs + 1, 0);
	}

	lua_pop(lua::L, 1);
}