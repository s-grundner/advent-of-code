// ------------------------------------------------------------
// https://adventofcode.com/2022/day/5
// ------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 40
#define INPUT_FILE "input.txt"
#define DELIM_STACK " []"
#define DELIM_INST " "

// #define DEBUG

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

	// count max stack height (line count to stack id line)
	char line[INPUT_SIZE];
	char ch;
	while (ch != '1')
	{
		ch = fgetc(file);
		cargo->max_stack_height += (ch == '\n');
	}
	// got back to the beginning of the stack id line (line length is always at max there)
	fseek(file, (-2) * sizeof(char), SEEK_CUR);
	// count max stack count (line length)
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
		cargo->stacks[i].content = (char*)malloc(cargo->max_stack_height * sizeof(char));
		cargo->stacks[i].size = 0;
	}
#ifdef DEBUG
	printf("max stack height: %d, max stack count: %d, instruction count: %d\n", cargo->max_stack_height, cargo->max_stack_count, cargo->instruction_count);
#endif
}

void fill_cargo(char* filename, cargo_t* cargo)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error opening file %s", filename);
		return;
	}

	// generate stack data struct from file
	char ch;
	char spaces = 0;
	int i = 0;
	int current_stack_height = cargo->max_stack_height - 1;
	while (ch = fgetc(file), current_stack_height >= 0)
	{
		spaces += (ch == ' ');
		if (ch == '[')
		{
			ch = fgetc(file);
			cargo->stacks[i].content[current_stack_height] = ch;
			spaces = 0;
			cargo->stacks[i].size++;
			cargo->stacks[i].max_size = cargo->stacks[i].size;
			i %= cargo->max_stack_height;
			i++;
		}
		else if (spaces >= 4)
		{
			cargo->stacks[i].content[current_stack_height] = '\0';
			i %= cargo->max_stack_height;
			spaces = 0;
			i++;
		}
		if (ch == '\n')
		{
			current_stack_height--;
			i = 0;
		}
	}

	// generate instruction data struct from file
	instruction_t* first_instruction = cargo->instructions;
	char line[INPUT_SIZE];
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

	cargo->instructions = first_instruction; // reset pointer to first instruction
	fclose(file);
}

void free_cargo(cargo_t* cargo)
{
	for (int i = 0; i < cargo->max_stack_count; i++)
		free(cargo->stacks[i].content);
	free(cargo->stacks);
	free(cargo->instructions);
}

void restack_cargo1(cargo_t* cargo)
{
#ifdef DEBUG
	if (cargo->finished_instructions >= 10)
#else
	// return if all instructions are finished
	if (cargo->finished_instructions >= cargo->instruction_count)
#endif
	{
		// realloc according to final size
		for (int i = 0; i < cargo->max_stack_count; i++)
			cargo->stacks[i].content = (char*)realloc(cargo->stacks[i].content, cargo->stacks[i].size * sizeof(char));
		return;
	}

	int src_stack_id = cargo->instructions[cargo->finished_instructions].src_stack_id - 1;
	int dest_stack_id = cargo->instructions[cargo->finished_instructions].dest_stack_id - 1;
	int items_to_move = cargo->instructions[cargo->finished_instructions].items_to_move;

#ifdef DEBUG
	int src_stack_size = cargo->stacks[src_stack_id].size; // dont use this, use cargo->stacks[src_stack_id].size instead
	int dest_stack_size = cargo->stacks[dest_stack_id].size; // dont use this, use cargo->stacks[dest_stack_id].size instead

	printf("Instruction %3d: Moving %2d items from stack %d (%2d|%2d|%2d) to stack %d (%2d|%2d|%2d)\n",
		cargo->finished_instructions,
		cargo->instructions[cargo->finished_instructions].items_to_move,
		src_stack_id,
		cargo->stacks[src_stack_id].size,
		cargo->stacks[src_stack_id].size - items_to_move,
		cargo->stacks[src_stack_id].max_size,
		dest_stack_id,
		cargo->stacks[dest_stack_id].size,
		cargo->stacks[dest_stack_id].size + items_to_move,
		cargo->stacks[dest_stack_id].max_size);
#endif
	// realloc destination stack if needed
	if (cargo->stacks[dest_stack_id].size + items_to_move > cargo->stacks[dest_stack_id].max_size)
	{
#ifdef DEBUG
		printf("---------- Reallocated %d for stack %d ----------\n",
			cargo->stacks[dest_stack_id].size + items_to_move, dest_stack_id);
#endif
		cargo->stacks[dest_stack_id].content = realloc(cargo->stacks[dest_stack_id].content, (cargo->stacks[dest_stack_id].size + 1 + items_to_move) * sizeof(char));
		cargo->stacks[dest_stack_id].max_size = cargo->stacks[dest_stack_id].size + items_to_move;
	}
	// concat item by item to destination stack and trim from source stack
	for (int i = 0; i < items_to_move; i++)
	{
		cargo->stacks[dest_stack_id].size++;
		strcat(cargo->stacks[dest_stack_id].content, &cargo->stacks[src_stack_id].content[cargo->stacks[src_stack_id].size - 1]);
		cargo->stacks[src_stack_id].size--;
		cargo->stacks[src_stack_id].content[cargo->stacks[src_stack_id].size] = '\0';
	}

#ifdef DEBUG
	if (cargo->stacks[src_stack_id].size < 0)
	{
		printf("Error: stack %d is empty (%d)\n", src_stack_id, cargo->stacks[src_stack_id].size);
		return;
	}
	for (int i = 0; i < cargo->max_stack_count; i++)
		printf("[id: %d] [sz: %2d]: %s\n", i, cargo->stacks[i].size, cargo->stacks[i].content);
	printf("\n");
#endif

	cargo->finished_instructions++; // goto next instruction
	return restack_cargo1(cargo); // recursive call
}

void restack_cargo2(cargo_t* cargo)
{
#ifdef DEBUG
	if (cargo->finished_instructions >= 10)
#else
	// return if all instructions are finished
	if (cargo->finished_instructions >= cargo->instruction_count)
#endif
	{
		// realloc according to final size
		for (int i = 0; i < cargo->max_stack_count; i++)
			cargo->stacks[i].content = (char*)realloc(cargo->stacks[i].content, cargo->stacks[i].size * sizeof(char));
		return;
	}

	int src_stack_id = cargo->instructions[cargo->finished_instructions].src_stack_id - 1;
	int dest_stack_id = cargo->instructions[cargo->finished_instructions].dest_stack_id - 1;
	int items_to_move = cargo->instructions[cargo->finished_instructions].items_to_move;

#ifdef DEBUG
	int src_stack_size = cargo->stacks[src_stack_id].size; // dont use this, use cargo->stacks[src_stack_id].size instead
	int dest_stack_size = cargo->stacks[dest_stack_id].size; // dont use this, use cargo->stacks[dest_stack_id].size instead

	printf("Instruction %3d: Moving %2d items from stack %d (prev: %2d|cur: %2d|max: %2d) to stack %d (%2d|%2d|%2d)\n",
		cargo->finished_instructions,
		cargo->instructions[cargo->finished_instructions].items_to_move,
		src_stack_id,
		cargo->stacks[src_stack_id].size,
		cargo->stacks[src_stack_id].size - items_to_move,
		cargo->stacks[src_stack_id].max_size,
		dest_stack_id,
		cargo->stacks[dest_stack_id].size,
		cargo->stacks[dest_stack_id].size + items_to_move,
		cargo->stacks[dest_stack_id].max_size);
#endif

	// realloc destination stack if needed
	if (cargo->stacks[dest_stack_id].size + items_to_move > cargo->stacks[dest_stack_id].max_size)
	{
#ifdef DEBUG
		printf("---------- Reallocated %d for stack %d ----------\n",
			cargo->stacks[dest_stack_id].size + items_to_move, dest_stack_id);
#endif
		cargo->stacks[dest_stack_id].content = realloc(cargo->stacks[dest_stack_id].content, (cargo->stacks[dest_stack_id].size + 1 + items_to_move) * sizeof(char));
		cargo->stacks[dest_stack_id].max_size = cargo->stacks[dest_stack_id].size + items_to_move;
	}

	// concat whole item section to destination stack and trim from source stack
	cargo->stacks[dest_stack_id].size += items_to_move;
	strcat(cargo->stacks[dest_stack_id].content,
		&cargo->stacks[src_stack_id].content[cargo->stacks[src_stack_id].size - items_to_move]);
	cargo->stacks[src_stack_id].size -= items_to_move;
	cargo->stacks[src_stack_id].content[cargo->stacks[src_stack_id].size] = '\0';

#ifdef DEBUG
	if (cargo->stacks[src_stack_id].size < 0)
	{
		printf("Error: stack %d is empty (%d)\n", src_stack_id, cargo->stacks[src_stack_id].size);
		return;
	}
	for (int i = 0; i < cargo->max_stack_count; i++)
		printf("[id: %d] [sz: %2d]: %s\n", i, cargo->stacks[i].size, cargo->stacks[i].content);
	printf("\n");
#endif
	cargo->finished_instructions++; // goto next instruction
	return restack_cargo2(cargo); // recursive call
}

char* top_of_each_stack(cargo_t* cargo)
{
	char* top_of_each;
	for (int i = 0; i < cargo->max_stack_count; i++)
		top_of_each[i] = cargo->stacks[i].content[cargo->stacks[i].size - 1];
	return top_of_each;
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

int main(int argc, char const* argv[])
{
	cargo_t cargo;
	init_cargo(INPUT_FILE, &cargo);
	fill_cargo(INPUT_FILE, &cargo);
	// restack_cargo1(&cargo);
	// restack_cargo2(&cargo);
	printf("%s\n", top_of_each_stack(&cargo));
	free_cargo(&cargo);
	return 0;
}
