#include "sol.hpp"
#include "library.h"
#include "common.h"
#include "EventDispatcher.h"
#include <iostream>

#include "Ogre.h"
using namespace Gsage;

class Woop
{
};

class Library : public EventDispatcher, public Woop
{
public:
  Library() {};
  virtual ~Library() {};
  const char* hello()
  {
    return "library";
  }
};

void Registrar::registerBindings(lua_State* L)
{
  sol::state_view lua(L);

  lua["test"] = [] (EventDispatcher* b) {
    if(b == NULL) {
      std::cout << "Got NULL" << "\n";
    }
  };

  lua.new_usertype<Library>("Library",
    sol::base_classes, sol::bases<Woop, EventDispatcher>()
  );
  lua.new_usertype<Ogre::Camera>("Camera");
}