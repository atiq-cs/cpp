#pragma once

// Forward Declaration is in this header file

class CShape;

class FD
{
public:
  FD(void);
  ~FD(void);
  void initialize();
  void display_shape();

private:
  CShape *uni_obj;
};
