// ------------------------------------------------------------
// https://adventofcode.com/2022/day/7
// ------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_FILE "input.txt"
#define INPUT_SIZE 256

// #define DEBUG

struct folder_s {
	char* name;
	int size;
	int dir_count;
	int depth;
	struct folder_s** sub_folders;
	struct folder_s* parent;
};
typedef struct folder_s folder_t;

typedef struct {
	folder_t* root;
	folder_t* current;
} filesystem_t;

// ------------------------------------------------------------
// FUNCTION DECLARATIONS
// ------------------------------------------------------------

void mkfs(filesystem_t* fs, char* root_name);
void mkdir(filesystem_t* fs, char* name);
void cd(filesystem_t* fs, char* path);

void print_tree(folder_t* folder, int level);
void update_size(folder_t* folder, int size);

// ------------------------------------------------------------
// UTILS
// ------------------------------------------------------------

void revert_from_history(filesystem_t* fs, char* hist_file)
{
	FILE* file = fopen(hist_file, "r");
	if (file == NULL) {
		printf("Error: could not open file %s\n", hist_file);
		return;
	}

	char line[INPUT_SIZE];
	while (fgets(line, sizeof(line), file)) {

		line[strcspn(line, "\n")] = 0; // remove newline and carriage return
		line[strcspn(line, "\r")] = 0; // remove carriage return

		if (line[0] == '$')
		{
			char* command = strtok(line, "$ ");
			char* arg = strtok(NULL, " ");
#ifdef DEBUG
			printf("command: %s, arg: %s\n", command, arg);
#endif
			if (strcmp(command, "cd") == 0) cd(fs, arg);
		}
		else if (line[0] != 'd')
		{
			char* f_size = strtok(line, " ");
			update_size(fs->current, atoi(f_size));
		}
	}
	fclose(file);
}

void print_tree(folder_t* folder, int depth)
{
	for (int i = 0; i < depth; i++) printf("|  ");
	printf("|->[%d] %s\n", folder->size, folder->name);

	if (folder->sub_folders)
		for (int i = 0; i < folder->dir_count; i++)
			print_tree(folder->sub_folders[i], depth + 1);
}

int sum_tree(folder_t* folder, int depth, int sum_smaller_than)
{
	int sum = 0;
	if (folder->sub_folders)
		for (int i = 0; i < folder->dir_count; i++)
			sum += sum_tree(folder->sub_folders[i], depth + 1, sum_smaller_than);
	if (folder->size < sum_smaller_than)
		sum += folder->size;
	return sum;
}

folder_t* find_optimal_folder_to_delete_for_update(folder_t* folder, int depth, int sum_greater_than)
{
	if (folder->sub_folders)
		for (int i = 0; i < folder->dir_count; i++)
		{
			folder_t* found = folder_to_delete(folder->sub_folders[i], depth + 1, sum_greater_than);
			if (found) return found;
		}
	if (folder->size > sum_greater_than)
		return folder;
	return NULL;
}

void free_folder(folder_t* folder)
{
	if (folder->sub_folders)
	{
		for (int i = 0; i < folder->dir_count; i++)
			free_folder(folder->sub_folders[i]);
		free(folder->sub_folders);
	}
	free(folder->name);
	free(folder);
}

// ------------------------------------------------------------
// COMMANDS
// ------------------------------------------------------------

void mkfs(filesystem_t* fs, char* root_name)
{
	if (!(fs->root = (folder_t*)malloc(sizeof(folder_t)))) return;
	if (!(fs->root->name = (char*)malloc(strlen(root_name) + 1))) return;
	strcpy(fs->root->name, root_name);
	fs->root->sub_folders = NULL;
	fs->root->parent = NULL;
	fs->root->depth = 0;
	fs->current = fs->root;
	fs->current->dir_count = 0;
}

void mkdir(filesystem_t* fs, char* name)
{
	for (int i = 0; i < fs->current->dir_count; i++)
	{
		if (strcmp(fs->current->sub_folders[i]->name, name) == 0)
		{
			printf("%s already exists\n", name);
			return;
		}
	}

	if (!(fs->current->sub_folders = (folder_t**)realloc(fs->current->sub_folders, (fs->current->dir_count + 1) * sizeof(folder_t*)))) return;
	if (!(fs->current->sub_folders[fs->current->dir_count] = (folder_t*)malloc(sizeof(folder_t)))) return;
	if (!(fs->current->sub_folders[fs->current->dir_count]->name = (char*)malloc(strlen(name) + 1))) return;

#ifdef DEBUG
	printf("mkdir: %s\n", name);
#endif

	strcpy(fs->current->sub_folders[fs->current->dir_count]->name, name);
	fs->current->sub_folders[fs->current->dir_count]->sub_folders = NULL;
	fs->current->sub_folders[fs->current->dir_count]->depth = fs->current->depth + 1;
	fs->current->sub_folders[fs->current->dir_count]->parent = fs->current;
	fs->current->dir_count++;
}

void update_size(folder_t* folder, int size)
{
	folder->size += size;
	if (folder->parent) update_size(folder->parent, size);
}

void cd(filesystem_t* fs, char* path)
{
	if (strcmp(path, ".") == 0) return;
	if (strcmp(path, "..") == 0)
	{
		if (strcmp(fs->current->name, "/")) fs->current = fs->current->parent;
#ifdef DEBUG
		printf("parenting to: %s\n", fs->current->name);
#endif
		return;
	}
	if (strcmp(path, "/") == 0)
	{
		fs->current = fs->root;
		return;
	}

	for (int i = 0; i < fs->current->dir_count; i++)
	{
		if (strcmp(fs->current->sub_folders[i]->name, path) == 0)
		{
			printf("cd %s to %s\n", fs->current->name, fs->current->sub_folders[i]->name);
			fs->current = fs->current->sub_folders[i];
			return;
		}
	}
	mkdir(fs, path);
	fs->current = fs->current->sub_folders[fs->current->dir_count - 1];
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

#define MIN_FREE_SPACE 30000000
#define MAX_SPACE 70000000
#define MIN_USED_SPACE (MAX_SPACE - MIN_FREE_SPACE)

int main(int argc, char const* argv[])
{
	filesystem_t fs;
	mkfs(&fs, "/");
	revert_from_history(&fs, HISTORY_FILE);
	printf("size of small dirs: %d\n", sum_tree(fs.root, 0, 100000));
	printf("folder size to delete for update: %d\n", find_optimal_folder_to_delete_for_update(fs.root, 0, fs.root->size - MIN_USED_SPACE)->size);
	free_folder(fs.root);
	return 0;
}