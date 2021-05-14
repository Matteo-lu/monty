#include "monty.h"

int _value;

/**
 * main - entry point, file reading and execution
 * @av: Double pointer with arguments
 * @ac: Number of arguments
 * Return: 0 if success or -1 if fail
 */
int main(int ac, char **av)
{
	char *buffer = NULL, **token = NULL;
	unsigned int number_lines = 1;
	stack_t *stack = NULL;
	size_t size  = 0;
	FILE *fp = fopen(av[1], "r");

	if (!fp)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	while (-1 != getline(&buffer, &size, fp))
	{
		number_lines++;
		token = buff_separator(buffer, " ");
		if (execute_loop(token, number_lines, &stack) == -1)
		{
			dprintf(STDERR_FILENO, "L%d: usage: push integer\n", number_lines);
			free_everything(buffer, &stack, token);
			exit(EXIT_FAILURE);
		}
	}
	buffer = NULL;
	/*free_everything(buffer, &stack, token);*/
	free(buffer);
	free_stack(&stack);
	fclose(fp);
	return (0);
}

/**
 * execute_loop - Execution loop
 * @array_lines: pointer to arguments
 * @number_lines: current line
 * @stack: pointer to top
 * Return: 0 if success or -1 if fail
 */
int execute_loop(char **array_lines, unsigned int
number_lines, stack_t **stack)
{
	unsigned int j = 0;

	while (array_lines[j] && j < 2)
	{
		j++;
	}
	if (j == 2)
	{
		_value = atoi(array_lines[1]);
		if (_value == 0 && strcmp(array_lines[1], "0") != 0)
		{
			free(array_lines);
			return (-1);
		}
	}
	if (j != 0)
	{
		get_func(array_lines[0], stack, number_lines);
	}
	free(array_lines);
	return (0);
}

/**
 * free_everything - function to free memory
 * @array_lines: pointer to arguments
 * @buffer: buffer
 * @stack: pointer to top
 * Return: void
 */
void free_everything(char *buffer, stack_t **stack, char **array_lines)
{
	free_stack(stack);
	free(buffer);
	free(array_lines);
}
