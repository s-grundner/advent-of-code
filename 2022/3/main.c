// ------------------------------------------------------------
// https://adventofcode.com/2022/day/3
// ------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG

#define INPUT_FILE "input.txt"
#define INPUT_SIZE 80
#define GROUP_SIZE 3

typedef struct
{
	char* compartment_one;
	char* compartment_two;
	char* all_compartments;

	char most_common;
	int capacity;
	int common_occurrences;
} *rucksack_t;

// ------------------------------------------------------------
// UTIL
// ------------------------------------------------------------

int count_rucksacks(char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error opening file %s", filename);
		return -1;
	}

	int rucksack_count = 0;
	char line[INPUT_SIZE];

	while (fgets(line, sizeof(line), file) != NULL)
		rucksack_count += (line[0] != '\n');
	fclose(file);
	return rucksack_count;
}

char count_char_in_string(char* str, char c)
{
	char count = 0;
	for (int i = 0; i < strlen(str); i++)
		count += (str[i] == c);
	return count;
}

char get_most_common_char(char* str, char* exclude)
{
	char most_common = 0;
	char most_common_count = 0;
	char current_count = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		if (count_char_in_string(exclude, str[i]) == 0)
		{
			current_count = count_char_in_string(str, str[i]);
			if (current_count > most_common_count)
			{
				most_common = str[i];
				most_common_count = current_count;
			}
		}
	}
	return most_common;
}

void calc_most_common(rucksack_t rucksacks)
{
	char* exclude = (char*)malloc(sizeof(char) * (rucksacks->capacity / 2 + 1));
	char common = get_most_common_char(rucksacks->all_compartments, exclude);

	int char_is_in_1 = count_char_in_string(rucksacks->compartment_one, common);
	int char_is_in_2 = count_char_in_string(rucksacks->compartment_two, common);

	int i = 0;
	while (!(char_is_in_1 && char_is_in_2))
	{
		exclude[i] = common;
		common = get_most_common_char(rucksacks->all_compartments, exclude);
		char_is_in_1 = count_char_in_string(rucksacks->compartment_one, common);
		char_is_in_2 = count_char_in_string(rucksacks->compartment_two, common);
		i++;
		if (i > rucksacks->capacity / 2)
			break;
	}
	rucksacks->most_common = common;
	rucksacks->common_occurrences = char_is_in_1 + char_is_in_2;

#ifdef DEBUG
	printf("Cap: %2d -> All: %52s -> Items: %26s %26s -> Most common: %c [%d,%d]-> excl: %s",
		rucksacks->capacity, rucksacks->all_compartments,
		rucksacks->compartment_one, rucksacks->compartment_two, common, char_is_in_1, char_is_in_2, exclude);
#endif
	free(exclude);
}

int sum_priorities(rucksack_t rucksacks, const int rucksack_count)
{
	int sum = 0;
	rucksack_t first_rucksack;
	for (first_rucksack = rucksacks; rucksacks - first_rucksack < rucksack_count; rucksacks++)
		sum += (rucksacks->most_common > 'Z') ? (rucksacks->most_common - 'a' + 1) : (rucksacks->most_common - 'A' + 27);
	return sum;
}

int group_elves(rucksack_t rucksacks, const int rucksack_count)
{
	int sum = 0;
	char* grouped_items = (char*)malloc(sizeof(char) * (150 + 1));
	for (int i = 0; i < rucksack_count; i += 3)
	{
		int grouped_capacity = rucksacks[i].capacity + rucksacks[i + 1].capacity + rucksacks[i + 2].capacity;
		grouped_items[0] = '\0';
		grouped_items = (char*)realloc(grouped_items, sizeof(char) * (grouped_capacity + 1));

		for (int j = 0; j < GROUP_SIZE; j++)
			strcat(grouped_items, rucksacks[i + j].all_compartments);

		char* exclude = (char*)malloc(sizeof(char) * (58 + 1));
		exclude[0] = '\0';
		char common = get_most_common_char(grouped_items, exclude);

		int char_is_in_1 = count_char_in_string(rucksacks[i].all_compartments, common);
		int char_is_in_2 = count_char_in_string(rucksacks[i + 1].all_compartments, common);
		int char_is_in_3 = count_char_in_string(rucksacks[i + 2].all_compartments, common);
		int k = 0;

		while (!(char_is_in_1 && char_is_in_2 && char_is_in_3))
		{
			exclude[k] = common;
			common = get_most_common_char(grouped_items, exclude);
			char_is_in_1 = count_char_in_string(rucksacks[i].all_compartments, common);
			char_is_in_2 = count_char_in_string(rucksacks[i + 1].all_compartments, common);
			char_is_in_3 = count_char_in_string(rucksacks[i + 2].all_compartments, common);
			k++;
			exclude[k] = '\0';
			if (k > 58)
				break; //
		}
		sum += (common > 'Z') ? (common - 'a' + 1) : (common - 'A' + 27);
#ifdef DEBUG
		// printf("Sum: %4d -> Iter: %2d -> Group: %2d -> Badge: [%c] -> Prio: %2d -> Grouped items: %s\n",
		// 	sum, k, i / 3, common, (common > 'Z') ? (common - 'a' + 1) : (common - 'A' + 27), exclude
		// );
#endif
		free(exclude);
	}
	free(grouped_items);
	return sum;
}

rucksack_t fill_rucksacks(char* filename, const int rucksack_count)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error opening file %s", filename);
		return NULL;
	}

	char line[INPUT_SIZE];
	rucksack_t rucksacks = malloc(rucksack_count * sizeof(*rucksacks));
	rucksack_t first_rucksack = rucksacks;

	while (fgets(line, sizeof(line), file) != NULL && (rucksacks - first_rucksack) < rucksack_count)
	{
		if (line[0] == '\n')
			continue;

		for (rucksacks->capacity = 0; line[rucksacks->capacity] != '\n'; ++rucksacks->capacity); // count capacity
		rucksacks->compartment_one = (char*)malloc(sizeof(char) * (rucksacks->capacity / 2 + 1));
		rucksacks->compartment_two = (char*)malloc(sizeof(char) * (rucksacks->capacity / 2 + 1));
		rucksacks->all_compartments = (char*)malloc(sizeof(char) * (rucksacks->capacity + 1));

		for (int i = 0; i < rucksacks->capacity / 2; i++)
		{
			rucksacks->compartment_one[i] = line[i];
			rucksacks->compartment_two[i] = line[i + rucksacks->capacity / 2];
			rucksacks->all_compartments[i] = line[i];
			rucksacks->all_compartments[i + rucksacks->capacity / 2] = line[i + rucksacks->capacity / 2];
		}
#ifdef DEBUG
		printf("Rucksack: %3d -> ", rucksacks - first_rucksack);
#endif
		calc_most_common(rucksacks);
#ifdef DEBUG

		printf("\n");
#endif
		rucksacks++;
	}
	rucksacks = first_rucksack;
	return rucksacks;
}

void free_rucksacks(rucksack_t rucksacks, const int rucksack_count)
{
	rucksack_t first_rucksack = rucksacks;
	for (int i = 0; i < rucksack_count; i++)
	{
		free(rucksacks->compartment_one);
		free(rucksacks->compartment_two);
		free(rucksacks->all_compartments);
		rucksacks++;
	}
	rucksacks = first_rucksack;
	free(rucksacks);
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

int main(int argc, char const* argv[])
{
	const int rucksack_count = count_rucksacks(INPUT_FILE);
	rucksack_t rucksacks = fill_rucksacks(INPUT_FILE, rucksack_count);
	printf("Sum of priorities: %d\n", sum_priorities(rucksacks, rucksack_count));
	printf("Sum of badges: %d\n", group_elves(rucksacks, rucksack_count));
	free_rucksacks(rucksacks, rucksack_count);
	return 0;
}
