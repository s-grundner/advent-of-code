// ------------------------------------------------------------
// https://adventofcode.com/2022/day/5
// ------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 80
#define INPUT_FILE "input.txt"
#define DELIM_STACK " []"
#define DELIM_INST " "

// ------------------------------------------------------------
// UTIL
// ------------------------------------------------------------

typedef struct
{
	int items_to_move;
	int src_stack_id;
	int dest_stack_id;
} instruction_t;

typedef struct
{
	int size;
	int max_size;
	char* content; // each char is an item
} stack_t;
typedef struct
{
	int max_stack_height;
	int max_stack_count;
	int instruction_count;
	int finished_instructions;
	stack_t* stacks;
	instruction_t* instructions;
} cargo_t;

char count_char_in_string(char* str, char c)
{
	char count = 0;
	for (int i = 0; i < strlen(str); i++)
		count += (str[i] == c);
	return count;
}

int stoi(char* str)
{
	int result = 0;
	for (int i = 0; i < strlen(str); i++)
		result = result * 10 + (str[i] - '0');
	return result;
}

void init_cargo(char* filename, cargo_t* cargo)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error opening file %s", filename);
		return;
	}

	cargo->max_stack_height = 0;
	cargo->instruction_count = 0;
	cargo->finished_instructions = 0;

	char line[INPUT_SIZE];
	char ch;
	while (ch != '1')
	{
		ch = fgetc(file);
		cargo->max_stack_height += (ch == '\n');
	}
	rewind(file);
	fgets(line, sizeof(line), file);
	for (cargo->max_stack_count = 0; line[cargo->max_stack_count] != '\0'; ++cargo->max_stack_count);
	cargo->max_stack_count /= 4;
	while (fgets(line, sizeof(line), file) != NULL)
		cargo->instruction_count += (line[0] == 'm');
	fclose(file);

	cargo->instructions = (instruction_t*)malloc(cargo->instruction_count * sizeof(instruction_t));
	cargo->stacks = (stack_t*)malloc(cargo->max_stack_count * sizeof(stack_t));

	for (int i = 0; i < cargo->max_stack_count; i++)
	{
		cargo->stacks[i].content = (char*)malloc((cargo->max_stack_height) * sizeof(char));
		cargo->stacks[i].size = cargo->max_stack_height;
	}
}

void fill_cargo(char* filename, cargo_t* cargo)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error opening file %s", filename);
		return;
	}

	instruction_t* first_instruction = cargo->instructions;
	char line[INPUT_SIZE];
	int current_stack_height = cargo->max_stack_height - 1;
	while (fgets(line, sizeof(line), file) != NULL)
	{
		if (line[0] == 'm')
		{
			char* token = strtok(line, DELIM_INST);
			token = strtok(NULL, DELIM_INST);
			cargo->instructions->items_to_move = atoi(token);
			token = strtok(NULL, DELIM_INST);
			token = strtok(NULL, DELIM_INST);
			cargo->instructions->src_stack_id = atoi(token);
			token = strtok(NULL, DELIM_INST);
			token = strtok(NULL, DELIM_INST);
			cargo->instructions->dest_stack_id = atoi(token);
			cargo->instructions++;
		}
	}

	char ch;

	while (ch = fgetc(file), ch != '1')
	{
		// if ch = [ then fgetc = value
		// count spaces, if 4 spaces in row ten value= '#'

	}

	cargo->instructions = first_instruction;
	fclose(file);
}

void free_cargo(cargo_t* cargo)
{
	for (int i = 0; i < cargo->max_stack_count; i++)
		free(cargo->stacks[i].content);
	free(cargo->stacks);
	free(cargo->instructions);
}

// recursive function to reorganize items in stack according to instruction
void restack_cargo(cargo_t* cargo)
{
	if (cargo->finished_instructions >= cargo->instruction_count)
	{
		for (int i = 0; i < cargo->max_stack_count; i++)
			printf("%s [%d]\n", cargo->stacks[i].content, cargo->stacks[i].size);
		return;
	}
	int src_stack_id = cargo->instructions[cargo->finished_instructions].src_stack_id;
	int dest_stack_id = cargo->instructions[cargo->finished_instructions].dest_stack_id;
	int items_to_move = cargo->instructions[cargo->finished_instructions].items_to_move;

	printf("Instruction %3d: Moving %3d items from stack %d(%3d|%3d) to stack %d(%3d|%3d) -> Max: %2d\n",
		cargo->finished_instructions + 1,
		cargo->instructions[cargo->finished_instructions].items_to_move,
		cargo->instructions[cargo->finished_instructions].src_stack_id,
		cargo->stacks[src_stack_id].size,
		cargo->stacks[src_stack_id].size - items_to_move,
		cargo->instructions[cargo->finished_instructions].dest_stack_id,
		cargo->stacks[dest_stack_id].size,
		cargo->stacks[dest_stack_id].size - items_to_move,

		cargo->max_stack_height);

	cargo->stacks[dest_stack_id].size += items_to_move;
	cargo->stacks[src_stack_id].size -= items_to_move;

	// if (cargo->stacks[dest_stack_id].size > cargo->stacks[dest_stack_id].max_size)
	// {
	// 	if (!realloc(cargo->stacks[dest_stack_id].content, cargo->stacks[dest_stack_id].size * sizeof(char)))
	// 	{
	// 		printf("Error reallocating memory for stack %d", dest_stack_id);
	// 		return;
	// 	}
	// 	printf("---------- Reallocated %d for stack %d ----------\n",
	// 		cargo->stacks[dest_stack_id].size, dest_stack_id);
	// 	cargo->stacks[dest_stack_id].max_size = cargo->stacks[dest_stack_id].size;
	// }
	// if (cargo->stacks[src_stack_id].size < 0)
	// {
	// 	printf("Error: stack %d is empty (%d)\n", src_stack_id, cargo->stacks[src_stack_id].size);
	// 	// return;
	// }
	cargo->finished_instructions++;
	return restack_cargo(cargo);
}


// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

int main(int argc, char const* argv[])
{
	cargo_t cargo;
	init_cargo(INPUT_FILE, &cargo);
	fill_cargo(INPUT_FILE, &cargo);
	printf("max stack height: %d, max stack count: %d, instruction count: %d\n", cargo.max_stack_height, cargo.max_stack_count, cargo.instruction_count);
	// restack_cargo(&cargo);
	free_cargo(&cargo);
	return 0;
}
