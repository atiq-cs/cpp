#include "Shape.h"

CShape::CShape(void)
{
}

CShape::CShape(int x) {
  a = x;
}

CShape::~CShape(void)
{
}

int CShape::get() {
  return a;
}