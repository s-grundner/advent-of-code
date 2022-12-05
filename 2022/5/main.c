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

// ------------------------------------------------------------
// UTIL
// ------------------------------------------------------------

typedef struct
{
	int move;
	int from;
	int to;
} instruction_t;

typedef struct
{
	int max_stack_height;
	int max_stack_count;
	char** stack_contents;
	int instruction_count;
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
	cargo->max_stack_count = 0;
	cargo->instruction_count = 0;

	char line[INPUT_SIZE];

	while (fgets(line, sizeof(line), file) != NULL)
	{
		if (line[1] == '1')
		{
			int len;
			for (len = 0; line[len] != '\0'; ++len);
			cargo->max_stack_count = len / 4;
		}
		cargo->max_stack_height += (line[0] != '\n' && line[0] != 'm');
		cargo->instruction_count += (line[0] == 'm');
	}

	fclose(file);
	cargo->max_stack_height--; // subtract line with numbers
}

void fill_cargo(char* filename, cargo_t* cargo)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error opening file %s", filename);
		return;
	}

	cargo->instructions = (instruction_t*)malloc(cargo->instruction_count * sizeof(instruction_t));
	cargo->stack_contents = (char**)malloc(cargo->max_stack_count * sizeof(char*));
	for (int i = 0; i < cargo->max_stack_count; i++)
		cargo->stack_contents[i] = (char*)malloc(cargo->max_stack_height * sizeof(char));

	instruction_t* first_instruction = cargo->instructions;
	char line[INPUT_SIZE];

	int current_stack_height = cargo->max_stack_height - 1;

	while (fgets(line, sizeof(line), file) != NULL)
	{
		// print indent count
		if (line[0] == 'm')
		{
			char* token = strtok(line, DELIM_INST);
			token = strtok(NULL, DELIM_INST);
			cargo->instructions->move = atoi(token);
			token = strtok(NULL, DELIM_INST);
			token = strtok(NULL, DELIM_INST);
			cargo->instructions->from = atoi(token);
			token = strtok(NULL, DELIM_INST);
			token = strtok(NULL, DELIM_INST);
			cargo->instructions->to = atoi(token);
			cargo->instructions++;
		}
		else if (line[0] != '\n' && line[1] != '1')
		{
			char* token = strtok(line, DELIM_STACK);
			for (int i = 0; i < cargo->max_stack_count * 4; i += 4)
			{
				if (line[i] == ' ' && line[i + 1] == ' ' && line[i + 2] == ' ' && line[i + 3] == ' ')
				{
					cargo->stack_contents[i / 4][current_stack_height] = '#';
				}
				else
				{
					cargo->stack_contents[i / 4][current_stack_height] = token[0];
					token = strtok(NULL, DELIM_STACK);
				}
			}
			current_stack_height--;
		}
	}
	cargo->instructions = first_instruction;
	fclose(file);
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

int main(int argc, char const* argv[])
{
	cargo_t cargo;
	init_cargo(INPUT_FILE, &cargo);
	fill_cargo(INPUT_FILE, &cargo);
	// print instructions
	// for (int i = 0; i < cargo.instruction_count; i++)
	// {
	// 	printf("move %2d from %2d to %2d\n", cargo.instructions[i].move, cargo.instructions[i].from, cargo.instructions[i].to);
	// }

	// print stack con

	// print cargo stack amounts
	printf("max stack height: %d, max stack count: %d, instruction count: %d\n", cargo.max_stack_height, cargo.max_stack_count, cargo.instruction_count);

	for (int i = 0; i < cargo.max_stack_count; i++)
	{
		printf("%s\n", cargo.stack_contents[i]);
		free(cargo.stack_contents[i]);
	}
	printf("\n");
	free(cargo.stack_contents);
	free(cargo.instructions);
	return 0;
}
