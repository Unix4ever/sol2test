#ifndef BASE_H
#define BASE_H

#include "ExportCommon.h"

class COMMON_API Base
{
public:
  Base();
  virtual ~Base();

  virtual const char* hello();
private:
  void privateMethod();
};
#endif
