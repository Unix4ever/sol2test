
#ifndef LIBRARY_H
#define LIBRARY_H

#include "sol.hpp"
#include "ExportCommon.h"

struct lua_State;

class LIBRARY_API Registrar
{
public:
  void registerBindings(lua_State* L);
};

#endif
