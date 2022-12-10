#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_LEN 100

// Function prototypes
void move_knots(char direction, int* row, int* col);
void update_tail(int* tail_row, int* tail_col, int head_row, int head_col);

int main()
{
    // Initialize variables
    int head_row = 0, head_col = 0, tail_row = 0, tail_col = 0;
    char direction;
    int steps;
    char line[ROW_LEN];
    char* input_file = "input.txt";
    FILE* fp;
    int visited[ROW_LEN][ROW_LEN];
    int count = 0;

    // Open input file
    fp = fopen(input_file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: Could not open file '%s'.\n", input_file);
        exit(EXIT_FAILURE);
    }

    // Initialize visited array
    memset(visited, 0, sizeof visited);

    // Read input from file
    while (fgets(line, ROW_LEN, fp) != NULL)
    {
        // Parse direction and number of steps from input line
        sscanf(line, "%c %d", &direction, &steps);

        printf("Direction: %c, Steps: %d\n", direction, steps);


        // Move the head of the rope
        for (int i = 0; i < steps; i++)
        {
            move_knots(direction, &head_row, &head_col);
            update_tail(&tail_row, &tail_col, head_row, head_col);

            // If the tail is visiting a new position, update count
            if (!visited[tail_row][tail_col])
            {
                visited[tail_row][tail_col] = 1;
                count++;
            }
        }
    }

    // Close input file
    fclose(fp);

    // Print the final position of the tail and the number of positions visited
    printf("Tail: (%d, %d)\n", tail_row, tail_col);
    printf("Positions visited: %d\n", count);

    return 0;
}
// Move the knots in the specified direction
void move_knots(char direction, int* row, int* col)
{
    // Move the head of the rope
    switch (direction)
    {
    case 'U':
        (*row)--;
        break;
    case 'D':
        (*row)++;
        break;
    case 'L':
        (*col)--;
        break;
    case 'R':
        (*col)++;
        break;
    }
}

// Update the position of the tail based on the movement of the head
void update_tail(int* tail_row, int* tail_col, int head_row, int head_col)
{
    // If the head is two steps directly up, down, left, or right from the tail,
    // move the tail one step in that direction
    if (abs(head_row - *tail_row) == 2)
    {
        *tail_row += (head_row > *tail_row) ? 1 : -1;
    }
    else if (abs(head_col - *tail_col) == 2)
    {
        *tail_col += (head_col > *tail_col) ? 1 : -1;
    }
    // If the head and tail are not touching and not in the same row or column,
    // move the tail one step diagonally to keep up with the head
    else if (head_row != *tail_row && head_col != *tail_col)
    {
        *tail_row += (head_row > *tail_row) ? 1 : -1;
        *tail_col += (head_col > *tail_col) ? 1 : -1;
    }
}
