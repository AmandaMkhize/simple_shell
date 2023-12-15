#include "shell.h"

/**
* print_error - Displays an error message
* @user_input: Input recieved from the user
* @counter: Count of shell loop
* @argv: Arguments before program starts(argv[0] == Shell Program Name)
*/

void print_error(char *user_input, int counter, char **argv)
{
char *error = _itoa(counter);

PRINT(argv[0]);
PRINT(": ");
PRINT(error);
PRINT(": ");
PRINT(user_input);
PRINT(": ");
PRINT("not found\n");

free(error);
}

/**
*  _prerror - Prints custom Error
* @argv: Arguments before program starts(argv[0] == Shell Program Name)
* @c: Error Count
* @cmd: Array of parsed command strings
*/

void _prerror(char **argv, int c, char **cmd)
{
char *error = _itoa(c);

PRINT(argv[0]);
PRINT(": ");
PRINT(error);
PRINT(": ");
PRINT(cmd[0]);
PRINT(": Illegal number: ");
PRINT(cmd[1]);
PRINT("\n");
free(error);
}

/**
* error_file - Prints custom Error
* @argv: Arguments before program starts(argv[0] == Shell Program Name)
* @c: Error Count
*/
void error_file(char **argv, int c)
{
char *error = _itoa(c);

PRINT(argv[0]);
PRINT(": ");
PRINT(error);
PRINT(": Cannot open ");
PRINT(argv[1]);
PRINT("\n");
free(error);
}
