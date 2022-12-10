// ------------------------------------------------------------
// https://adventofcode.com/2022/day/8
// ------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "test.txt"
#define INPUT_SIZE 105

int main(int argc, char const* argv[])
{

	FILE* fp = fopen(INPUT_FILE, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Could not open file '%s'.\n", INPUT_FILE);
	}

	// count the number of lines in the file
	int line_count = 5;
	int line_length = 5;
	char line[INPUT_SIZE];
	// fgets(line, INPUT_SIZE, fp);
	// for (line_length = 0; line[line_length] != '\0'; line_length++);
	// rewind(fp);
	// while (fgets(line, INPUT_SIZE, fp) != NULL)
	// 	line_count++;
	// rewind(fp);
	int forest[line_count][line_length];
	line_count = 0;

	while (fgets(line, INPUT_SIZE, fp) != NULL)
	{
		// remove \n and \r
		line[strcspn(line, "\r")] = '\0';
		line[strcspn(line, "\n")] = '\0';

		for (int i = 0; i < line_length; i++)
			forest[line_count][i] = line[i];
		line_count++;
	}

	int visible_tree_count = 0;
	for (int i = 0; i < line_count; i++) {
		for (int j = 0; j < line_length; j++) {
			int is_visible = 1;
			if (is_visible) {
				visible_tree_count++;
			}
		}
	}
	printf("%d\n", visible_tree_count);
	return 0;
}
