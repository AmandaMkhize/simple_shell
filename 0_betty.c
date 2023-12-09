#include <unistd.h>

/**
* main - Entry point
* Description: A simple C program that prints "Simple Shell"
* Return: Always 0
*/
int main(void)
{
write(1, "Simple Shell\n", 1);
return (0);
}
