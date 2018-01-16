
#ifndef LIBRARY_H
#define LIBRARY_H

struct lua_State;

class Registrar
{
public:
  void registerBindings(lua_State* L);
};

#endif
