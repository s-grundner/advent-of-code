// ------------------------------------------------------------
// https://adventofcode.com/2022/day/4
// ------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 15
#define INPUT_FILE "input.txt"

#define DELIM ",-"

typedef struct
{
	int assign_one[2];
	int assign_two[2];
} *assignment_pair_t;

typedef struct
{
	assignment_pair_t assignments;
	int fully_overlapping_count;
	int partly_overlapping_count;
} management_list_t;

// ------------------------------------------------------------
// UTIL
// ------------------------------------------------------------

int stoi(char *str)
{
	int i = 0;
	int num = 0;
	while (str[i] != '\0')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return num;
}

int count_assignments(char *filename)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error opening file %s", filename);
		return -1;
	}

	int assign_count = 0;
	char line[INPUT_SIZE];

	while (fgets(line, sizeof(line), file) != NULL)
		assign_count += (line[0] != '\n');
	fclose(file);
	return assign_count;
}

int is_fully_overlapping(int a, int b, int c, int d)
{
	return (a <= c && b >= d) || (c <= a && d >= b);
}

int is_partly_overlapping(int a, int b, int c, int d)
{
	return (a <= c && b >= c) || (c <= a && d >= a);
}

management_list_t manage_assignments(char *filename, int assign_count)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error opening file %s", filename);
		return (management_list_t){NULL, 0, 0};
	}

	char line[INPUT_SIZE];
	management_list_t management_list;
	assignment_pair_t pairs = malloc(assign_count * sizeof(*pairs));
	management_list.fully_overlapping_count = 0;
	management_list.partly_overlapping_count = 0;
	assignment_pair_t first_pair = pairs;

	while (fgets(line, sizeof(line), file) != NULL && (pairs - first_pair) < assign_count)
	{
		if (line[0] == '\n')
			continue;

		pairs->assign_one[0] = stoi(strtok(line, "-,-\n"));
		pairs->assign_one[1] = stoi(strtok(NULL, "-,-\n"));
		pairs->assign_two[0] = stoi(strtok(NULL, "-,-\n"));
		pairs->assign_two[1] = stoi(strtok(NULL, "-,-\n"));

		management_list.fully_overlapping_count += is_fully_overlapping(pairs->assign_one[0], pairs->assign_one[1], pairs->assign_two[0], pairs->assign_two[1]);
		management_list.partly_overlapping_count += is_partly_overlapping(pairs->assign_one[0], pairs->assign_one[1], pairs->assign_two[0], pairs->assign_two[1]);

		pairs++;
	}
	pairs = first_pair;
	management_list.assignments = pairs;
	return management_list;
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

int main(int argc, char const *argv[])
{
	int assign_count = count_assignments(INPUT_FILE);
	management_list_t management_list = manage_assignments(INPUT_FILE, assign_count);
	printf("Number of full overlaps: %d\n", management_list.fully_overlapping_count);
	printf("Number of partly overlaps: %d\n", management_list.partly_overlapping_count);
	free(management_list.assignments);
	return 0;
}
