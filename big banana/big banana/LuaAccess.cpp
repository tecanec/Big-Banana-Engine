#include <iostream>
#include "LuaPackage.h"
#include "LuaAccess.h"


lua_State *lua::L = luaL_newstate();


lua::LuaObject::LuaObject()
{
}


lua::LuaObject::~LuaObject()
{

}


// Pushes the object last pulled from the stack by this LuaObject using Set()
void lua::LuaObject::Get()
{
	if (hasValue)
	{
		lua_pushlightuserdata(L, (void*)this);
		lua_gettable(L, LUA_REGISTRYINDEX);
	}
	else
		lua_pushnil(L);
}


// Takes the object on the top of the stack and holds onto it so that it can be retrieved with Get()
void lua::LuaObject::Set()
{
	lua_pushlightuserdata(L, (void*)this);
	lua_pushvalue(L, -2);
	lua_settable(L, LUA_REGISTRYINDEX);
	hasValue = !lua_isnil(L, -1);
	lua_pop(L, 1);
}


bool lua::LuaObject::HasValue()
{
	return hasValue;
}



void lua::runMethod(int table, int nargs, int nresults)
{
	lua_gettable(L, table);
	lua_insert(L, -(nargs + 1));
	lua_pushvalue(L, table);
	lua_insert(L, -(nargs + 1));
	lua_call(L, nargs + 1, nresults);
}