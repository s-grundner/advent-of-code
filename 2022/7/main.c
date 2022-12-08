// ------------------------------------------------------------
// https://adventofcode.com/2022/day/7
// ------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_FILE "test.txt"
#define INPUT_SIZE 256

#define DEBUG

typedef struct {
	char* name;
	int size;
} file_t;

struct folder_s {
	char* name;
	int size;
	int dir_count;
	int file_count;
	file_t* files;
	struct folder_s** sub_folders;
	struct folder_s* parent;
};
typedef struct folder_s folder_t;

typedef struct {
	folder_t* root;
	folder_t* current;
} filesystem_t;

void mkfs(filesystem_t* fs, char* root_name);
void mkdir(filesystem_t* fs, char* name);
void touch(filesystem_t* fs, char* name);
void cd(filesystem_t* fs, char* path);
void ls(folder_t* folder);

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

		line[strcspn(line, "\n")] = 0; // remove newline

		if (line[0] == '$')
		{
			char* command = strtok(line, "$ ");
			char* arg = strtok(NULL, " ");
			if (strcmp(command, "cd") == 0) cd(fs, arg);
		}
	}
	fclose(file);
}

// ------------------------------------------------------------
// COMMANDS
// ------------------------------------------------------------

void mkfs(filesystem_t* fs, char* root_name)
{
	if (!(fs->root = (folder_t*)malloc(sizeof(folder_t)))) return;
	fs->root->name = root_name;
	fs->root->files = NULL;
	fs->root->sub_folders = NULL;
	fs->root->parent = NULL;
	fs->current = fs->root;

	// revert_from_history(fs, HISTORY_FILE);
}

void mkdir(filesystem_t* fs, char* name)
{
	if (!(fs->current->sub_folders = (folder_t**)realloc(fs->current->sub_folders, (fs->current->dir_count + 1) * sizeof(folder_t*)))) return;
	if (!(fs->current->sub_folders[fs->current->dir_count] = (folder_t*)malloc(sizeof(folder_t)))) return;

#ifdef DEBUG
	printf("mkdir: %s\n", name);
#endif

	fs->current->sub_folders[fs->current->dir_count]->name = name;
	fs->current->sub_folders[fs->current->dir_count]->files = NULL;
	fs->current->sub_folders[fs->current->dir_count]->sub_folders = NULL;
	fs->current->sub_folders[fs->current->dir_count]->parent = fs->current;
	fs->current->dir_count++;
}

void touch(filesystem_t* fs, char* name)
{
	if (!(fs->current->files = (file_t*)realloc(fs->current->files, (fs->current->file_count + 1) * sizeof(file_t)))) return;

	fs->current->files[fs->current->file_count].name = name;
	fs->current->files[fs->current->file_count].size = 0;
	fs->current->file_count++;
}

void cd(filesystem_t* fs, char* path)
{
	if (strcmp(path, "..") == 0)
	{
#ifdef DEBUG
		printf("parenting into: %s %s\n", fs->current->name, fs->current->parent);
#endif
		// fs->current = fs->current->parent;
		return;
	}
	mkdir(fs, path);


	if (strcmp(path, "/") == 0)
	{
		fs->current = fs->root;
		return;
	}

	for (int i = 0; i < fs->current->dir_count; i++)
	{
		if (strcmp(fs->current->sub_folders[i]->name, path) == 0)
		{
			// print subfolder name
#ifdef DEBUG
			printf("cd: %s\n", fs->current->sub_folders[i]->name);
#endif
			fs->current = fs->current->sub_folders[i];
			return;
		}
	}

	mkdir(fs, path);
	fs->current = fs->current->sub_folders[fs->current->dir_count - 1];
}

void ls(folder_t* folder)
{

}

void printfs(filesystem_t* fs)
{
	printf("root/\n");
	for (int i = 0; i < fs->root->dir_count; i++)
	{
		printf("|->%s\n", fs->root->sub_folders[i]->name);
	}
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

int main(int argc, char const* argv[])
{
	filesystem_t fs;
	mkfs(&fs, "/");

	// mkdir(&fs, "home");
	mkdir(&fs, "etc");
	cd(&fs, "home");

	printf("current: %s\n", fs.current->name);

	printfs(&fs);

	return 0;
}
