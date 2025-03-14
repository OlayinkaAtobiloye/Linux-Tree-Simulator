#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int findCmd(char *cmd){
    char *cmds[] = {"mkdir", "rmdir", "cd", "creat", "rm", "ls", "pwd", "save", "reload", "quit", NULL};
    int index = 0;
    while (cmds[index]){
        if (strcmp(cmds[index], cmd)==0){
            return index;
        }
        index++;
    }
    return -1;
}

int main(){
    FileSystem fs;
    initialize(&fs);
    char line[65];
    char index;
    int quit_flag = 1;
    char command[65];
    char pathname[65];
    typedef int (*fptr)(FileSystem *, char *);
    fptr fptrs[] = {mkdir_, rmdir_, cd_, creat_, rm_, ls_, pwd_, save_, reload_, quit_};

    while(quit_flag){
        printf("Enter a command: ");
        fgets(line, 65, stdin);
        sscanf(line, "%s %s", command, pathname);
        index = findCmd(command);
        if (index==-1){
            printf("Invalid command! \n");
            continue;
        }
        fptrs[index](&fs, pathname);
        if (strcmp(command, "quit")==0){
            quit_flag = 0;
        }
    }
    return 1;
}
