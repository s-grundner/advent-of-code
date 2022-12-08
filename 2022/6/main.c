// ------------------------------------------------------------
// https://adventofcode.com/2022/day/6
// ------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"
#define INPUT_SIZE 5001

// ------------------------------------------------------------
// UTIL
// ------------------------------------------------------------

// check all characters in a string for multiple occurrences in the given interval

int check_for_double_chars(char* str, int start, int end)
{
	int count = 0;
	for (int i = start; i < end; i++)
		for (int j = i + 1; j < end; j++)
			if (str[i] == str[j])
				return 1;
	return 0;
}

int decrypt_markers(char* input_file, int marker_interval)
{
	FILE* fp = fopen(input_file, "r");
	if (fp == NULL)
	{
		printf("Error opening file %s", input_file);
		return -1;
	}

	int first_marker_at = 0;
	char line[INPUT_SIZE];
	fgets(line, INPUT_SIZE, fp);

	int actual_length = 0;
	for (actual_length = 0; line[actual_length] != '\0'; actual_length++);

	while (check_for_double_chars(line, first_marker_at, first_marker_at + marker_interval))
	{
		first_marker_at++;
		if (first_marker_at > actual_length)
		{
			return -1;
			printf("No marker found\n");
		}
	}
	first_marker_at += marker_interval;

	fclose(fp);
	return first_marker_at;
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

int main(int argc, char const* argv[])
{
	printf("First marker at: %d\n", decrypt_markers(INPUT_FILE, 4));
	printf("First marker at: %d\n", decrypt_markers(INPUT_FILE, 14));
	return 0;
}
