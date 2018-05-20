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
void lua::LuaObject::Push()
{
	lua_pushlightuserdata(L, (void*)&key);
	lua_gettable(L, LUA_REGISTRYINDEX);
}


// Takes the object on the top of the stack holds onto it so that it can be retrieved with Push()
void lua::LuaObject::Pull()
{
	lua_pushlightuserdata(L, (void*)&key);
	lua_pushvalue(L, -2);
	lua_settable(L, LUA_REGISTRYINDEX);
	lua_pop(L, 1);
}