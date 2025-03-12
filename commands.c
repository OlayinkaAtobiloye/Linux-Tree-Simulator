#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void printFileSystem(FileSystem *fs){
    
}

int mkdir_(FileSystem *fs, char *pathname){
    char dname[64], bname[64];
    dbname(pathname, dname, bname);
    NODE* parentNode = searchDir(fs, dname);
    NODE* newNode = newDirectoryNode(bname);
    if (!parentNode) {
        printf("Invalid pathname!\n");
        return 0;
    }
    if (parentNode->nodeType != 'D'){
        printf("Not a directory! \n");
    }
    if (!parentNode->childPtr){
        parentNode->childPtr = newNode;
        newNode->parentPtr = parentNode;
    }
    else {
        NODE *t = parentNode->childPtr;
        while(t->siblingPtr && strcmp(t->name, bname)!=0){
            t = t->siblingPtr;
        };
        if (strcmp(t->name, bname) ==0){
            printf("Directory already exists! \n");
            return 0;
        }
        t->siblingPtr = newNode;
        newNode->parentPtr = t;
    }
    printf("Directory created successfully!\n");
    return 1;
}

int rmdir_(FileSystem* fs, char *pathname){
    if (strlen(pathname) == 0){
        printf("Path cannot be empty! \n");
        return 0;
    }
    char dname[64], bname[64];
    dbname(pathname, dname, bname);
    NODE* parentDir = searchDir(fs, dname);
    NODE* dirToRemove = parentDir->childPtr;
    if (!parentDir){
        printf("Invalid pathname! \n");
        return 0;
    }

    while (dirToRemove && strcmp(bname, dirToRemove->name)!=0){
        dirToRemove = dirToRemove->siblingPtr;
    }

    if (dirToRemove == NULL){
        printf("Directory does not exist! \n");
        return 0;
    }
    if (dirToRemove->nodeType != 'D'){
        printf("Pathname not a directory! \n");
        return 0;
    }
    if (dirToRemove->childPtr != NULL){
        printf("Directory not empty and cannot be removed! \n");
        return 0;
    }
    if (dirToRemove->parentPtr == parentDir){
        dirToRemove->parentPtr->childPtr = dirToRemove->siblingPtr;
        if (dirToRemove->siblingPtr){
            dirToRemove->siblingPtr->parentPtr = dirToRemove->parentPtr;
        }
    }
    else{
        dirToRemove->parentPtr->siblingPtr = dirToRemove->siblingPtr;
         if (dirToRemove->siblingPtr){
            dirToRemove->siblingPtr->parentPtr = dirToRemove->parentPtr;
        }
    }
    printf("Directory successfully deleted! \n");
    
    return 1;
}

int cd_(FileSystem *fs, char *pathname){
    if (strlen(pathname)==0){
        fs->cwd = fs->root;
        printf("Directory changed successfully! n");
        return 1;
    }
    char dname[64], bname[64];
    dbname(pathname, dname, bname);
    NODE* parentDir = searchDir(fs, dname);
    if (!parentDir){
        printf("Invalid pathname parent! \n");
        printf("%s %s", dname, bname);
        return 0;
    }
    
    if (strcmp(pathname, "..")==0){
        if (fs->cwd->parentPtr != NULL) {
            fs->cwd = fs->cwd->parentPtr;
        }
        printf("Directory changed successfully!\n");
        return 1;
    }
    if (strcmp(pathname, "~")==0){
        fs->cwd = fs->root;
        printf("Directory changed successfully!\n");
        return 1;
    }
    NODE* t = parentDir;
    if (strcmp(bname, ".") != 0 && strcmp(bname, "/")!=0){
        t = parentDir->childPtr;
        while (t && strcmp(t->name, bname)!=0){
            t = t->siblingPtr;
        }
    }
    if (t == NULL){
        printf("Invalid pathname node! \n");
        return 0;
    }
    if(t->nodeType == 'F'){
        printf("File not a directory! \n");
        return 0;
    }
    fs->cwd = t;
    printf("Directory changed successfully! \n");
    return 1;
}



