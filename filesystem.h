typedef struct Node {
    char name[65];
    char nodeType;
    struct Node *childPtr;
    struct Node *siblingPtr;
    struct Node *parentPtr;
} NODE;

// filesystem structure
typedef struct FileSystem {
    NODE *root, *cwd;
} FileSystem;


void initialize(FileSystem *fs);
NODE* searchDir(FileSystem *fs, char *pathname);
NODE* newDirectoryNode(char *basename);
NODE* newFileNode(char *basename);
int dbname(char *pathname, char *dname, char *bname);

