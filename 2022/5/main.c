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
	int size;
	char* content;
} stack_t;
typedef struct
{
	int max_stack_height;
	int max_stack_count;
	int instruction_count;
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

	cargo->max_stack_height = 8;
	cargo->max_stack_count = 9;
	cargo->instruction_count = 0;

	char line[INPUT_SIZE];

	while (fgets(line, sizeof(line), file) != NULL)
	{
		// if (line[1] == '1')
		// {
		// 	int len;
		// 	for (len = 0; line[len] != '\0'; ++len);
		// 	cargo->max_stack_count = len / 4;
		// }
		// cargo->max_stack_height += (line[0] != '\n' && line[0] != 'm');
		cargo->instruction_count += (line[0] == 'm');
	}

	fclose(file);

	cargo->instructions = (instruction_t*)malloc(cargo->instruction_count * sizeof(instruction_t));
	cargo->stacks = (stack_t*)malloc(cargo->max_stack_count * sizeof(stack_t));

	for (int i = 0; i < cargo->max_stack_count; i++)
		cargo->stacks[i].content = (char*)malloc((cargo->max_stack_height - 1) * sizeof(char));

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
	int current_stack_height = cargo->max_stack_height;
	char line[INPUT_SIZE];
	while (fgets(line, sizeof(line), file) != NULL)
	{
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
			char* token = (char*)malloc((current_stack_height - 1) * sizeof(char));
			char* temp = token;
			char* temp2;
			token = strtok(line, DELIM_STACK);
			for (int i = 0; i < cargo->max_stack_count * 4 && current_stack_height >0; i += 4)
			{
				cargo->stacks[i / 4].size = count_char_in_string(line, ' ') / 4;
				if (line[i] == ' ' && line[i + 1] == ' ' && line[i + 2] == ' ' && line[i + 3] == ' ')
				{
					cargo->stacks[i / 4].content[current_stack_height] = '#';
				}
				else {
					cargo->stacks[i / 4].content[current_stack_height] = 'w';
					printf("%c%d ", *token, current_stack_height);
					token = strtok(NULL, DELIM_STACK);
				}
			}
			current_stack_height--;
			token = temp;
			free(token);
			printf("\n");
		}
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

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------

int main(int argc, char const* argv[])
{
	cargo_t cargo;
	init_cargo(INPUT_FILE, &cargo);
	fill_cargo(INPUT_FILE, &cargo);
	printf("max stack height: %d, max stack count: %d, instruction count: %d\n", cargo.max_stack_height, cargo.max_stack_count, cargo.instruction_count);
	for (int i = 0; i < cargo.max_stack_count; i++)
		printf("%s, %d", cargo.stacks[i].content, cargo.stacks[i].size);
	free_cargo(&cargo);
	return 0;
}
