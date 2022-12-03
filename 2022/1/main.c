// ------------------------------------------------------------
// https://adventofcode.com/2022/day/1
// ------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "input.txt"

// ------------------------------------------------------------
// UTILS
// ------------------------------------------------------------

int count_elves(char *file_name)
{
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		printf("Error opening file");
		return -1;
	}
	int elf_count = 0;
	char line[10];
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (line[0] == '\n')
		{
			elf_count++;
		}
	}
	return elf_count;
}

int *array_calories(char *file_name, int elf_count)
{
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		printf("Error opening file");
		return NULL;
	}
	int *cal_array = malloc(elf_count * sizeof(int));
	char line[10];
	int sum_current_cal = 0;
	int i = 0;
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (line[0] != '\n')
		{
			sum_current_cal += atoi(line);
		}
		else
		{
			cal_array[i] = sum_current_cal;
			sum_current_cal = 0;
			i++;
		}
	}
	fclose(fp);
	return cal_array;
}

int compare(const void *a, const void *b)
{
	return (*(int *)b - *(int *)a);
}

// ------------------------------------------------------------
// QUESTIONS
// ------------------------------------------------------------

// Question 1
int question_1(char *file_name)
{
	int elf_count = count_elves(file_name);
	int *cal_array = array_calories(file_name, elf_count);

	qsort(cal_array, elf_count, sizeof(int), compare);
	int elf_with_most_cal = cal_array[0];

	free(cal_array);
	return elf_with_most_cal;
}

// Question 2
int question_2(char *file_name, const int top_count)
{
	int elf_count = count_elves(file_name);
	int *cal_array = array_calories(file_name, elf_count);

	qsort(cal_array, elf_count, sizeof(int), compare);

	int top_sum_calories = 0;
	for (int i = 0; i < top_count; i++)
		top_sum_calories += cal_array[i];

	free(cal_array);
	return top_sum_calories;
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

int main(int argc, char const *argv[])
{
	printf("Question 1: %d\n", question_1(FILE_NAME));
	printf("Question 2: %d\n", question_2(FILE_NAME, 3));
	return 0;
}
