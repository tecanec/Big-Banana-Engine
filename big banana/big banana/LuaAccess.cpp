#include "LuaAccess.h"
#include "LuaPackage.h"


lua_State *L = luaL_newstate();


lua::LuaObject::LuaObject()
{
}


lua::LuaObject::~LuaObject()
{

}


// Pushes the object last pulled from the stack by this LuaObject
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


// Takes the object on the top of the stack holds onto it so that it can be retrieved with Push()
void lua::LuaObject::Set()
{
	lua_pushlightuserdata(L, (void*)this);
	lua_pushvalue(L, -2);
	lua_settable(L, LUA_REGISTRYINDEX);
	hasValue = !lua_isnil(L, -1);
	lua_pop(L, 1);
}