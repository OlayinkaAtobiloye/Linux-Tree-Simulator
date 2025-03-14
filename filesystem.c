#include "filesystem.h"
#include <string.h>
#include <libgen.h>
#include <stdlib.h>
#include <stdio.h>

void initialize(FileSystem *fs){
    fs->root = newDirectoryNode("");
    fs->cwd = fs->root;
}

NODE* newDirectoryNode(char *basename){
    NODE* newDir = (NODE *)malloc(sizeof(NODE));
    strcpy(newDir->name, basename);
    newDir->type = 'D';
    newDir->siblingPtr = newDir->parentPtr = newDir->childPtr = 0;
    return newDir;
}

NODE* newFileNode(char *basename){
    NODE* newFile = (NODE *)malloc(sizeof(NODE));
    strcpy(newFile->name, basename);
    newFile->type = 'F';
    newFile->siblingPtr = newFile->parentPtr = newFile->childPtr = 0;
    return newFile;
}


int dbname(char *pathname, char *dname, char *bname){
    char temp[128];
    strcpy(temp, pathname);
    strcpy(dname, dirname(temp));
    strcpy(temp, pathname);
    strcpy(bname, basename(temp));
    return 0;
}

NODE* searchDir(FileSystem *fs, char *pathname){
    if (strlen(pathname)==0 || strcmp(pathname, ".")==0){
        return fs->cwd;
    }
    if (strcmp(pathname, "/")==0){
        return fs->root;
    }
    NODE* curr = fs->cwd;
    if (pathname[0] == '/'){
       curr = fs->root;
    }
    char path[65];
    strcpy(path, pathname);
    char *s = strtok(path, "/");

    while(s && curr){
        if (curr->childPtr){
            curr = curr->childPtr;
        }
        while(curr && strcmp(curr->name, s)!=0){
            curr = curr->siblingPtr;
        }
        s = strtok(0, "/"); 
    }
    return curr;
}
