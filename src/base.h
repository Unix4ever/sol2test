#ifndef BASE_H
#define BASE_H
class Base
{
public:
  Base();
  virtual ~Base();

  virtual const char* hello();
private:
  void shlop();
};
#endif
