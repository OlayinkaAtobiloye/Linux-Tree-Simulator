#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mkdir_(FileSystem *fs, char *pathname){
    char dname[64], bname[64];
    dbname(pathname, dname, bname);
    NODE* parentNode = searchDir(fs, dname);
    NODE* newNode = newDirectoryNode(bname);
    if (!newNode) {
        printf("Failed to allocate memory for new directory!\n");
        return 0;
    }
    if (parentNode == NULL) {
        printf("Invalid pathname!\n");
        return 0;
    }
    if (parentNode->type != 'D'){
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
            free(newNode);
            return 0;
        }
        t->siblingPtr = newNode;
        newNode->parentPtr = t;
    }
    printf("Directory created successfully!\n");
    return 1;
}

int rmdir_(FileSystem *fs, char *path){
    char dname[65];
    char bname[65];
    dbname(path, dname, bname);
    NODE* parentDir = searchDir(fs, dname);
    if (parentDir == NULL){
        printf("Invalid pathanme");
        return 0;
    }
    NODE* t = parentDir->childPtr;
    while (t && strcmp(t->name, bname)!=0){
        t = t->siblingPtr;
    }
    if (t == NULL){
        printf("Invalid pathanme");
        return 0;
    }
    if (t->type != 'D'){
        printf("Not a directory! \n");
    }
    if (t->childPtr != NULL){
        printf("Directory not empty and cannot be removed! \n");
        return 0;
    }
    if (t->parentPtr == parentDir){
        t->parentPtr->childPtr = t->siblingPtr;
        if (t->siblingPtr){
            t->siblingPtr->parentPtr = t->parentPtr;
        }
    }
    else{
        t->parentPtr->siblingPtr = t->siblingPtr;
        if (t->siblingPtr){
            t->siblingPtr->parentPtr = t->parentPtr;
        }
    }
    printf("Directory successfully deleted! \n");
    
    return 1;
}

int cd_(FileSystem *fs, char *path){
    if (strlen(path)==0){
        fs->cwd = fs->root;
        printf("Directory changed successfully! n");
        return 1;
    }
    char dname[65];
    char bname[65];
    dbname(path, dname, bname);
    NODE* parentDir = searchDir(fs, dname);
    if (parentDir == NULL){
        printf("Invalid pathanme");
        return 0;
    }
    if (strcmp(path, "..")==0){
        if (fs->cwd->parentPtr != NULL) {
            fs->cwd = fs->cwd->parentPtr;
        }
        printf("Directory changed successfully!\n");
        return 1;
    }
    if (strcmp(path, "~")==0){
        fs->cwd = fs->root;
        printf("Directory changed successfully!\n");
        return 1;
    }
    NODE* t = parentDir->childPtr;
    while (t->siblingPtr && strcmp(t->name, bname)!=0){
        t = t->siblingPtr;
    }
    if (t == NULL){
        printf("Invalid pathanme");
        return 0;
    }
    if (t->type == 'F'){
        printf("File not a directory");
        return 0;
    }
    fs->cwd = t;
    printf("Directory changed successfully! \n");
    return 1;
}

int ls_(FileSystem *fs, char *path){
    char bname[65];
    char dname[65];
    dbname(path, dname, bname);
    NODE* parentDir = searchDir(fs, dname);
    if (!parentDir){
        printf("Invalid pathname! \n");
        return 0;
    }
    NODE *t = parentDir;
    if (strcmp(bname, ".")!=0 && strcmp(bname, "/")!=0){
        t = t->childPtr;
        while (t && strcmp(t->name, bname)!=0)
        {
            t = t->siblingPtr;
        }
    }
    if (!t){
        printf("Invalid pathname! \n");
        return 0;
    }
    if (t->type == 'D'){
        t = t->childPtr;
        while (t){
            printf("%s\t", t->name);
            t = t->siblingPtr;
        }
    }
    else{
        printf("%s\t", t->name);
    }
    printf("\n");
    return 1;
};

void pwdhelper(NODE* node){
    if (node == NULL)return;
    pwdhelper(node->parentPtr);
    if (node->parentPtr && node->parentPtr->childPtr == node){
        printf("%s/", node->parentPtr->name);
    }
}

int pwd_(FileSystem *fs, char *path){
    pwdhelper(fs->cwd);
    printf("%s/", fs->cwd->name);
    printf("\n");
    return 1;
};

void savehelper(FILE *fptr, char* prefix, NODE* node){
    if (node == NULL){
        return;
    }
    char temp[128];
    strcpy(temp, prefix);
    strcat(temp, "/");
    strcat(temp, node->name);

    fprintf(fptr, "%c\t\t%s", node->type, temp);
    savehelper(fptr, prefix, node->siblingPtr);
    savehelper(fptr, temp, node->childPtr);
}

int save_(FileSystem *fs, char *filename){
    if (!fs->root){
        printf("Uninitialized file system! \n");
        return 0;
    }
    FILE *fptr = fopen(filename, "w+");
    fprintf(fptr, "%c\t\t%s", fs->root->type, "/");
    savehelper(fptr, "/", fs->root->childPtr);
    return 1;
}

int reload_(FileSystem *fs, char *filename){
    FILE *fptr = fopen(filename, "r");
    if (!fptr){
        printf("No saved filesystem!");
        return 0;
    }

    char type;
    char pathName[128];
    fscanf(fptr, "%c\t\t%s", type, pathName);
    while (fscanf(fptr, "%c\t\t%s", type, pathName)==2)
    {
       if (type == 'D'){
        mkdir_(fs, pathName);
       }
       else{
        creat_(fs, pathName);
       }
    }
    

    fclose(fptr);
    return 1;

};

int quit_(FileSystem *fs, char *path){
    save_(fs, "FileSystem.txt");
    return 1;
}

int creat_(FileSystem *fs, char *path){
    char dname[65];
    char bname[65];
    dbname(path, dname, bname);
    NODE* parentDir = searchDir(fs, dname);
    if (parentDir == NULL){
        printf("Invalid pathanme! \n");
        return 0;
    }
    if (parentDir->type != 'D'){
        printf("Not a directory! \n");
    }
    NODE *t = parentDir;
    NODE* newFile = newFileNode(bname);
    if(t->childPtr == NULL){
        t->childPtr = newFile;
        newFile->parentPtr = t;
        printf("File created successfully! \n");
        return 1;
    }
    else {
        NODE *t = parentDir->childPtr;
        while(t->siblingPtr && strcmp(t->name, bname)!=0){
            t = t->siblingPtr;
        };
        if (strcmp(t->name, bname) ==0){
            printf("File already exists! \n");
            return 0;
        }
        t->siblingPtr = newFile;
        newFile->parentPtr = t;
    }
    printf("File created successfully! \n");
        return 1;
};

int rm_(FileSystem *fs, char *path){
    char dname[65];
    char bname[65];
    dbname(path, dname, bname);
    NODE* parentDir = searchDir(fs, dname);
    if (parentDir == NULL){
        printf("Invalid pathanme");
        return 0;
    }
    if (strcmp(path, "..")==0){
        if (fs->cwd->parentPtr != NULL) {
            fs->cwd = fs->cwd->parentPtr;
        }
        printf("Directory changed successfully!\n");
        return 1;
    }
    if (strcmp(path, "~")==0){
        fs->cwd = fs->root;
        printf("Directory changed successfully!\n");
        return 1;
    }
    NODE* t = parentDir->childPtr;
    while (t && strcmp(t->name, bname)!=0){
        t = t->siblingPtr;
    }
    if (t == NULL){
        printf("Invalid pathanme");
        return 0;
    }
    if (t->type != 'D'){
        printf("Not a directory! \n");
    }
    if (t->childPtr != NULL){
        printf("Directory not empty and cannot be removed! \n");
        return 0;
    }
    if (t->parentPtr == parentDir){
        t->parentPtr->childPtr = t->siblingPtr;
        if (t->siblingPtr){
            t->siblingPtr->parentPtr = t->parentPtr;
        }
    }
    else{
        t->parentPtr->siblingPtr = t->siblingPtr;
        if (t->siblingPtr){
            t->siblingPtr->parentPtr = t->parentPtr;
        }
    }
    printf("Directory successfully deleted! \n");
    
    return 1;
}

