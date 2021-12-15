# Shell-Terminal
A shell implementation using Linux processes for CS-333 Operating Systems course

## Code organization:
- At first the code reads the command from the user and put it in an array.
- Checks if the command exceeds 512 bytes and if so print ERROR.
- Checks if the command is empty and if so prints WARNING.
- Then code parses the data of the array and split it into smaller strings separated by spaces.
- It first checks if command is “cd” and if so it handles it.
- Code creates another process to handle execution.
- If the child process is addressed it executes the command
- The parent process waits for the child unless the command is in background

## Main functions:
- readCommand

This function takes input from the user and saves it in command array.
    
- isEmpty

This function is to indicate if the array is empty or not to handle this later.

- parse

This function is used to parse the input; it divides the array into many strings using a splitter (space) each terminated with NULL.
    
- excute

This function executes what is supplied in the arguments using execvp.

## How to run:
You only have to go to the directory and type make.
