#include "sol.hpp"
#include "common.h"
#include <iostream>

const char* Local::hello()
{
  return "local";
}

LuaRunner::LuaRunner()
{
}

LuaRunner::~LuaRunner()
{
}

void LuaRunner::reg()
{
  L = luaL_newstate();
  sol::state_view lua = sol::state_view(L);
  lua.open_libraries();

  lua.new_usertype<Base>("Base");
  lua.new_usertype<Local>("Local",
    sol::base_classes, sol::bases<Common, Base>()
  );

  lua["obj"] = &obj;
}

lua_State* LuaRunner::getState()
{
  return L;
}

void LuaRunner::run()
{
  sol::state_view lua(L);
  lua.script("print(obj);test(obj);");
}
