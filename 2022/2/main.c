// ------------------------------------------------------------
// https://adventofcode.com/2022/day/2
// ------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "input.txt"
#define INPUT_SIZE 4

#define ROCK_POINTS 1
#define PAPER_POINTS 2
#define SCISSORS_POINTS 3

// ------------------------------------------------------------
// UTIL
// ------------------------------------------------------------

typedef enum
{
	ROCK_P = 'X',
	PAPER_P = 'Y',
	SCISSORS_P = 'Z',
	ROCK_O = 'A',
	PAPER_O = 'B',
	SCISSORS_O = 'C'
} shape_t;

typedef enum
{
	LOSE_E = 'X',
	DRAW_E = 'Y',
	WIN_E = 'Z'
} strategy_outcome_t;

typedef struct
{
	shape_t opponent_shape;
	shape_t player_shape;
} *match_t;

int count_rounds(char *filename)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
		printf("Error opening file %s", filename);

	int match_count = 0;
	char line[INPUT_SIZE];

	while (fgets(line, sizeof(line), file) != NULL)
		match_count += (line[0] != '\n');

	return match_count;
}

match_t generate_match(char *filename, int round_count)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
		printf("Error opening file %s", filename);

	char line[INPUT_SIZE];
	match_t match = malloc(sizeof(match_t) * round_count);
	match_t start = match;

	while (fgets(line, sizeof(line), file) != NULL && (match - start) < round_count)
	{
		if (line[0] != '\n')
		{
			match->opponent_shape = (shape_t)line[0];
			match->player_shape = (shape_t)line[2];
			match++;
		}
	}

	match = start;
	fclose(file);
	return match;
}

int calculate_points1(match_t match, const int round_count)
{
	int points = 0;
	match_t start = match;
	for (int i = 0; i < round_count; i++)
	{
		if (match->player_shape == match->opponent_shape + (ROCK_P - ROCK_O))
			points += 3;
		else if (match->player_shape == ROCK_P && match->opponent_shape == SCISSORS_O)
			points += 6;
		else if (match->player_shape == PAPER_P && match->opponent_shape == ROCK_O)
			points += 6;
		else if (match->player_shape == SCISSORS_P && match->opponent_shape == PAPER_O)
			points += 6;
		points += 1 * (match->player_shape == ROCK_P) + 2 * (match->player_shape == PAPER_P) + 3 * (match->player_shape == SCISSORS_P);
		match++;
	}
	match = start;
	return points;
}

int calculate_points2(match_t match, const int round_count)
{
	int points = 0;
	match_t start = match;

	for (int i = 0; i < round_count; i++)
	{
		switch ((strategy_outcome_t)match->player_shape)
		{
		case LOSE_E:
			points += (match->opponent_shape == ROCK_O) * SCISSORS_POINTS;
			points += (match->opponent_shape == PAPER_O) * ROCK_POINTS;
			points += (match->opponent_shape == SCISSORS_O) * PAPER_POINTS;
			break;

		case DRAW_E:
			points += 3;
			points += (match->opponent_shape == ROCK_O) * ROCK_POINTS;
			points += (match->opponent_shape == PAPER_O) * PAPER_POINTS;
			points += (match->opponent_shape == SCISSORS_O) * SCISSORS_POINTS;
			break;
		case WIN_E:

			points += 6;
			points += (match->opponent_shape == ROCK_O) * PAPER_POINTS;
			points += (match->opponent_shape == PAPER_O) * SCISSORS_POINTS;
			points += (match->opponent_shape == SCISSORS_O) * ROCK_POINTS;
			break;
		}
		match++;
	}
	match = start;
	return points;
}

// ------------------------------------------------------------
//  MAIN
// ------------------------------------------------------------

int main(int argc, char const *argv[])
{
	int round_count = count_rounds(INPUT_FILE);
	match_t match = generate_match(INPUT_FILE, round_count);

	printf("Question 1: %d\n", calculate_points1(match, round_count));
	printf("Question 2: %d\n", calculate_points2(match, round_count));

	free(match);
	return 0;
}
