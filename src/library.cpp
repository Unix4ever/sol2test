#include "sol.hpp"
#include "library.h"
#include "common.h"
#include <iostream>

class LibraryBase
{

};

class BreakIt
{
public:
  BreakIt(const std::string& parameter)
  {

  }

  virtual ~BreakIt()
  {

  }
};

class Library : public Base, public LibraryBase
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

  lua.new_usertype<Library>("Library",
    sol::base_classes, sol::bases<LibraryBase, Base>()
  );

  lua.new_usertype<BreakIt>("BreakIt"
  );

  lua["test"] = [] (Base* b) {
    if(b == NULL) {
      std::cout << "Got NULL" << "\n";
    } else {
      std::cout << "Got object, ok \n";
    }
  };
}
