#include "filesystem.h"
#include <string.h>

int mkdir_(FileSystem *fs, char *path);
int rmdir_(FileSystem *fs, char *path);
int cd_(FileSystem *fs, char *path);
int creat_(FileSystem *fs, char *path);
int rm_(FileSystem *fs, char *path);
int ls_(FileSystem *fs, char *path);
int pwd_(FileSystem *fs, char *path);
int save_(FileSystem *fs, char *path);
int reload_(FileSystem *fs, char *path);
int quit_(FileSystem *fs, char *path);
