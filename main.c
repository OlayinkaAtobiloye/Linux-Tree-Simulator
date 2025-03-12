#include "commands.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>


char *cmds[] = {"mkdir", "rmdir", "cd", "ls", "pwd", "creat", "rm", "save", "reload", "menu", "quit", NULL};
int findCmd(char* cmd){
    int index = 0;
    while(cmds[index]){
        if (!strcmp(cmds[index], cmd)){
            return index;
        }
        index++;
    }
    return -1;
}

int main(){
    FileSystem fs;
    initialize(&fs);
    NODE* root, cwd;
    char line[128];
    char command[16], pathname[64];
    typedef int (*fptr)(FileSystem*, char*);
    fptr fptrs[] = {mkdir_, rmdir_, cd_};
    
    while(1){
        fgets(line, 128, stdin);
        line[strlen(line)- 1] = 0;
        sscanf(line, "%s %s", command, pathname);
        int index = findCmd(command);
        // switch (index){
        //     case 0:
        //         mkdir(pathname);
        //     case 1: 
        //         rmdir(pathname);
        //     default:
        //         printf("Invalid command %s \n", command);
        // }
        fptrs[index](&fs, pathname);

    }

}