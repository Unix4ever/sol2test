#ifndef COMMON_H
#define COMMON_H

#include "sol.hpp"
#include "base.h"

struct lua_State;

class COMMON_API Common
{

};

class COMMON_API Local : public Common, public Base
{
public:
  const char* hello();
};

class COMMON_API LuaRunner
{
public:
  LuaRunner();
  virtual ~LuaRunner();
  void run();
  void reg();
  lua_State* getState();
private:
  lua_State* L;
  Local obj;
};

#endif
