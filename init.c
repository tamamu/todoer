#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>

#ifdef __unix__
#include <sys/stat.h>
#define cmkdir(dir) mkdir(dir,0777)
#define RCNAME ".todoerc"
#elif defined _WIN32
#include <direct.h>
#define cmkdir(dir) _mkdir(dir)
#define RCNAME "todoer.cfg"
#endif
