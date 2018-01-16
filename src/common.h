#ifndef COMMON_H
#define COMMON_H

#include "EventDispatcher.h"
#include "sol.hpp"
#include "base.h"

using namespace Gsage;

struct lua_State;

class Base2 : public Base
{
public:
  Base2() {};
  virtual ~Base2() {}
};

class Base3
{
public:
  Base3() {};
  virtual ~Base3() {}
};

class Local : public Base, public EventDispatcher
{
public:
  Local() {};
  virtual ~Local() {};
  const char* hello();
};

class LuaRunner
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
