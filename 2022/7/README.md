# This code is an implementation of a very simple file system

## Functionality

- Initialize a new file system with a root folder.
- Create new folders within the current folder.
- Change the current folder to a sub-folder.
- Revert the file system state from a history file that stores the changes made to the file system.
- Print the folder tree.
- Compute the sum of all file sizes in the tree that are smaller than a given size.
- Find and delete a folder that has a file size greater than a given size.

## Structs

- `folder_t`: represents a folder in the file system.
- `filesystem_t`: represents the file system itself.

## Functions

- `mkfs()`: initializes a new file system with a root folder.
- `mkdir()`: creates a new folder within the current folder.
- `cd()`: changes the current folder to a sub-folder.
- `print_tree()`: prints the folder tree.
- `update_size()`: updates the size of a folder.
- `revert_from_history()`: reverts the file system state from a history file.
- `sum_tree()`: computes the sum of all file sizes in the tree that are smaller than a given size.
- `folder_to_delete()`: finds and returns a folder that has a file size greater than a given size.
- `free_folder()`: frees the memory allocated for a folder and its sub-folders.

## Issues

- The `revert_from_history()` function does not handle the case where the history file is empty or does not exist.
- The `revert_from_history()` function uses a fixed-size buffer to read lines from the history file.
- The `revert_from_history()` function uses the `strtok()` function to parse the commands and arguments in the history file.
- The `print_tree()` function uses the `printf()` function to print the folder tree.
- The `sum_tree()` and `folder_to_delete()` functions use a recursive approach that can cause stack overflow for deep folder trees.
