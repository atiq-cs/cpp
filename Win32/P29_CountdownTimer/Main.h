#include <windows.h>
#include <windowsx.h>
#include <iostream>
using namespace std;
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <strsafe.h>
#define _WIN32_IE 0x0500
#include <commctrl.h>

const bool BEEP = false;
const int winx = 375;
const int winy = 180;
long seconds = 0;
long secondsold = time (NULL);
long elapsedtime = 0; 
long lastactiveseconds = 0;
long daytime = 0;
long startdaytime = time (NULL);
long starttime = time (NULL);
int posx = 0;
int posy = 0;
int oldposx = 0;
int oldposy = 0;
bool closingdown = false;
NOTIFYICONDATA nid;
