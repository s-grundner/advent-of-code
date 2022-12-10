# Advent of Code 2022 - Day 5

The code reads an input file that describes a cargo arrangement and a set of instructions for moving items between the cargo's stacks. The code simulates the moving of items according to the instructions and outputs the final cargo arrangement.

The input file is expected to have the following format:

```
    [ ]     [ ] [ ] [ ]
    [ ]     [ ] [ ] [ ]
[ ] [ ]     [ ] [ ] [ ]
[ ] [ ] [ ] [ ] [ ] [ ]
[ ] [ ] [ ] [ ] [ ] [ ]
[ ] [ ] [ ] [ ] [ ] [ ]
 1   2   3   4   5   6   (stack id line)

move 1 from 2 to 1 (instruction 1)
move 1 from 3 to 1 (instruction 2)
move 1 from 4 to 1 (instruction 3)
...
```

The code is implemented in C and consists of several functions. The `init_cargo` function takes the name of the input file and a cargo structure as arguments, and initializes the structure with the contents of the input file. The `fill_cargo` function takes the same arguments as `init_cargo` and fills the cargo's stacks with the contents of the input file. The `execute_instruction` function takes a cargo structure and an instruction as arguments and simulates the execution of the given instruction on the cargo. The run_instructions function takes a cargo structure as an argument and executes all instructions on the cargo. The main function is the entry point of the program and ties all of these functions together to solve the puzzle.

The code uses a `cargo_t` structure to represent the cargo and its stacks. The structure contains the maximum number of stacks and the maximum height of a stack, as well as the number of instructions and an array of instructions and an array of stacks. Each stack is represented by a `stack_t` structure containing the number of items in the stack, the maximum number of items that the stack can hold, and an array of characters representing the items in the stack. Each instruction is represented by an `instruction_t` structure containing the number of items to move, the source stack id, and the destination stack id.
