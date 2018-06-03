#pragma once

namespace lua
{
	extern lua_State *L;

	class LuaObject
	{
	public:
		LuaObject();
		~LuaObject();

		// Pushes the object last pulled from the stack by this LuaObject using Set()
		void Get();
		// Takes the object on the top of the stack and holds onto it so that it can be retrieved with Get()
		void Set();

		// Does this have a value yet?
		bool HasValue();
	private:
		bool hasValue;
	};

	//Runs method table[i] where i is the value on top of the stack.
	void runMethod(int table, int nargs, int nresults);
}