#include "sol.hpp"
#include "common.h"
#include <iostream>
#include <windows.h>

const char* Local::hello()
{
  return "local";
}

void LuaRunner::reg()
{
  L = luaL_newstate();
  sol::state_view lua(L);

  lua.new_usertype<Base>("Base");
  lua.new_usertype<Local>("Local",
    sol::base_classes, sol::bases<Base>()
  );

  Local* b = new Local();
  lua["obj"] = b;
}

lua_State* LuaRunner::getState()
{
  return L;
}

void LuaRunner::run()
{
  sol::state_view lua(L);

  lua.unsafe_script("test(obj);");
}
