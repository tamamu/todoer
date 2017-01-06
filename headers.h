#ifndef _INCLUDE_HEADERS_
#define _INCLUDE_HEADERS_

#ifdef __unix__
#include <sys/stat.h>
#define cmkdir(dir) mkdir(dir,0777)
#define RCNAME ".todoerc"
#elif defined _WIN32
#include <direct.h>
#define cmkdir(dir) _mkdir(dir)
#define RCNAME "todoer.cfg"
#endif

#define cmd(match) strcmp(argv[argc],match)==0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>

#endif

#include "external.h"
