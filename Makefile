main: main.c commands.h commands.c filesystem.c filesystem.h
	gcc -o main main.c commands.c filesystem.c 