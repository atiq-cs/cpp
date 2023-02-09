//
// PURPOSE: Forward declaration of class
//
// Author : Atiq Rahman
// Date   : 02-15-2014
// Status : Good
// Remarks: Demos an OOP Feature
//         This style of FD is often found in MFC Application Programs
//


#include "FD.h"

int main () {
	FD FDObj;

	FDObj.initialize();
	FDObj.display_shape();

	return 0;
}