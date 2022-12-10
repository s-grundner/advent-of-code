# Advent of Code 2022 - Day 2
Elf Rock-Paper-Scissors Game

## Functions

- `count_rounds()`: counts the number of rounds in the input file.
- `generate_match()`: reads the choices of each elf for each round from the input file and returns an array of matches.
- `calculate_points1()`: calculates the points of the player based on the standard rock-paper-scissors rules.
- `calculate_points2()`: calculates the points of the player based on a modified set of rules, where the player can earn extra points by predicting their opponent's move.

## Issues

- The `count_rounds()` and `generate_match()` functions do not handle the case where the input file does not exist or is empty.
- The `generate_match()` function uses a fixed-size buffer to read lines from the input file. If a line in the file is longer than the buffer size, it will be truncated, which can lead to incorrect results. It would be better to use a dynamic buffer or a line-reading function that can handle long lines.
- The `generate_match()` function assumes that the input file has a specific format, where each line consists of a shape chosen by the player followed by a space and then a shape chosen by the opponent. If the input file does not have this format, the function will not parse the data correctly and the results will be incorrect. It would be better to add more robust parsing and error-handling to the function.
- The `calculate_points1()` and `calculate_points2()` functions use a series of `if` statements and a `switch` statement to determine the points scored by the player in each round. This can be difficult to read and maintain, and it can be error-prone if new rules are added or existing rules are changed. It would be better to refactor the code to use a more modular and extensible approach, such as defining
