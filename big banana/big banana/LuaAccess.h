#pragma once

namespace lua
{
	class LuaObject
	{
	public:
		LuaObject();
		~LuaObject();

		void Get();
		void Set();
	private:
		bool hasValue;
	};
}