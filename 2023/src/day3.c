/**
 * @file day3.c
 * @author Simon Grundner
 * @brief Advent of code puzzle day 3
 * @date 2023-12-03
 * @details https://adventofcode.com/2023/day/3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../inputs/day3.txt"
#define BUFSIZE 150
#define PREV 0
#define CURR 1
#define NEXT 2

#define GEAR '*'

#define is_num(x) (x >= '0' && x <= '9')

const char *symbols = "*#+$@&=/";

int day3_1()
{
	FILE *input = fopen(INPUT, "r");

	char line[3][BUFSIZE] = {0};

	fgets(line[CURR], sizeof(line[CURR]), input); // no symbols in first line
	while (fgets(line[NEXT], sizeof(line[NEXT]), input) != NULL)
	{
		// find all syms in line sym
		char *sym = line[CURR];

		int sym_idx = 0;
		for (char *sym = line[CURR]; sym - line[CURR] != sizeof(line[CURR]); sym += sym_idx + 1)
		{
			sym_idx = strcspn(sym, symbols);
			for (int i = 0; i < 3; i++) // i = PREV CURR NEXT line
			{
				for (int j = -1; j < 2; j++) // check around index
				{
					if (is_num(line[i][sym_idx + j]))
					{
						char *p = line[i] + sym_idx + j;
						while (is_num(*p))
						{
							p--;
						}
						printf("%d\n", atoi(p + 1));
					}
				}
			}
		}
		strcpy(line[PREV], line[CURR]);
		strcpy(line[CURR], line[NEXT]);
	}

	fclose(input);
	return 0;
}
int day3_2() { return 0; }

int main(int argc, char const *argv[])
{
	printf("Answer of day 3 part 1 is: %d \n", day3_1());
	printf("Answer of day 3 part 2 is: %d \n", day3_2());
	return 0;
}
