#ifndef COMMON_H
#define COMMON_H

#include "EventDispatcher.h"

using namespace Gsage;

struct lua_State;

class Base
{
public:
  Base() {};
  virtual ~Base() {}

  virtual const char* hello() = 0;
};

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

class Local : public Base2, public Base3, public EventDispatcher
{
public:
  Local() {};
  virtual ~Local() {};
  const char* hello();
};

class LuaRunner
{
public:
  void run();
  void reg();
  lua_State* getState();
private:
  lua_State* L;
};

#endif
