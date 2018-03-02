#ifndef __READY__
#define __READY__

//HEADER FILES FOR getchar_silent()
#include <stdio.h> 
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <stropts.h>

using namespace std;

int getchar_silent();

#endif