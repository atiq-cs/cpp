#pragma once

class CShape
{
public:
  CShape(void);
  CShape(int x);
  ~CShape(void);
  int get();

private:
  int a;
};
