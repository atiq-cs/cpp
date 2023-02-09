#include "FD.h"
#include "Shape.h"
#include <iostream>


FD::FD(void)
{
}

FD::~FD(void)
{
}

void FD::initialize() {
	uni_obj = new CShape(50);
}

void FD::display_shape() {
	std::cout<<"Retrieved value: "<<uni_obj->get()<<std::endl;
}