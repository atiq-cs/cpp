//
// PURPOSE: Convert Hexadecimal number to Decimal
//
// Date   : 2010 approx
// Status : 
// Remarks: Demos,
//        - base conversion
//

#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

unsigned long int ConvertHexStrToDec(char *str) {
	unsigned long int res;
	res = strtoul(str, 0, 16);
	return res;
}

int main (int argc, char* argv[]) {
	if (argc != 2) {
		puts("Invalid number of cmd line args");
		return 0;
	}

	char *hexString = argv[1];
	unsigned long int x = ConvertHexStrToDec(hexString);
	printf("The value represented by the string \"%s\" is\n"
"%lu (decimal)\n" "%#lo (octal)\n" "%#lx (hex)\n", hexString, x, x, x);

	return 0;
}
