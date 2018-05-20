#pragma once

namespace lua
{
	class LuaObject
	{
	public:
		LuaObject();
		~LuaObject();

		void Push();
		void Pull();
	private:
		char key;
	};
}