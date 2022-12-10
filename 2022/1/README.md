# Advent of Code 2022 - Day 1

The elves want to know the following:

- The elf with the most calories eaten.
- The sum of the top 3 elves with the most calories eaten.

The code contains the following functions to solve the problem:

## Functions

- `count_elves()`: counts the number of elves in the input file.
- `array_calories()`: reads the calorie intake of each elf from the input file and returns an array of the calorie counts.
- `question_1()`: returns the elf with the most calories eaten.
- `question_2()`: returns the sum of the top 3 elves with the most calories eaten.

## Issues

- The `count_elves()` and `array_calories()` functions do not handle the case where the input file does not exist or is empty.
- The `array_calories()` function uses a fixed-size buffer to read lines from the input file. If a line in the file is longer than the buffer size, it will be truncated, which can lead to incorrect results. It would be better to use a dynamic buffer or a line-reading function that can handle long lines.
- The `array_calories()` function uses the `atoi()` function to convert the calorie count strings to integers. This function does not check for errors, such as invalid input or overflow. It would be better to use a safer alternative, such as `strtol()` or `sscanf()`.
- The `compare()` function used for sorting the calorie counts is not defined in the code. It should be defined before it is used in the `qsort()` function.
- The `question_1()` and `question_2()` functions do not check for invalid input, such as negative calorie counts or negative values for the top count. It would be better to add validation and error-handling for such cases.
