
#ifndef LIBRARY_H
#define LIBRARY_H

#include "sol.hpp"

struct lua_State;

class Registrar
{
public:
  void registerBindings(lua_State* L);
};

#endif
