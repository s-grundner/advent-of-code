// ------------------------------------------------------------
// https://adventofcode.com/2022/day/5
// ------------------------------------------------------------	

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 100
#define INPUT_FILE "input.txt"

// ------------------------------------------------------------
// UTIL
// ------------------------------------------------------------

typedef struct
{
	char* line;
} *lines_t;

int count_lines(char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error opening file %s", filename);
		return -1;
	}

	int line_count = 0;
	char line[INPUT_SIZE];

	while (fgets(line, sizeof(line), file) != NULL)
		line_count += (line[0] != '\n');
	fclose(file);
	return line_count;
}

lines_t read_file(char* filename, int line_count)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error opening file %s", filename);
		return NULL;
	}

	lines_t lines = (lines_t)malloc(sizeof(lines_t) * line_count);
	lines_t first_line = lines;
	char line[INPUT_SIZE];

	while (fgets(line, sizeof(line), file) != NULL && (lines - first_line) < line_count)
	{
		if (line[0] == '\n')
			continue;

		lines++;
	}
	lines = first_line;
	return lines;
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

int main(int argc, char const* argv[])
{
	int line_count = count_lines(INPUT_FILE);
	lines_t lines = read_file(INPUT_FILE, line_count);
	free(lines);
	return 0;
}
