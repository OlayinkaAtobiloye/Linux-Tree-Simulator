# File System Simulation

This project is a simulation of a file system implemented in C. It includes basic file system operations such as creating directories, removing directories, and changing directories.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Functions](#functions)
- [Contributing](#contributing)
- [License](#license)

## Installation

To compile and run this project, you need to have a C compiler installed on your system. You can use `gcc` for this purpose.

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/filesystem-simulation.git
    cd filesystem-simulation
    ```

2. Compile the code:
    ```sh
    gcc -o filesystem main.c commands.c
    ```

3. Run the executable:
    ```sh
    ./filesystem
    ```

## Usage

The project provides several functions to interact with the simulated file system. Below are some examples of how to use these functions:

### Creating a Directory

```c
FileSystem fs;
initFileSystem(&fs);

### Removing a Directory
mkdir_(&fs, "/new_directory");rmdir_(&fs, "/new_directory");

### Changing a Directory
cd_(&fs, "/new_directory");

Functions
mkdir_(FileSystem *fs, char *pathname)
Creates a new directory at the specified pathname.

rmdir_(FileSystem *fs, char *pathname)
Removes the directory at the specified pathname if it is empty.

cd_(FileSystem *fs, char *pathname)
Changes the current working directory to the specified pathname.

printFileSystem(FileSystem *fs)
Prints the structure of the file system.

Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes.

License
This project is licensed under the MIT License. See the LICENSE file for details.

