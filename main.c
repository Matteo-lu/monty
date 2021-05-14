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
	unsigned int number_lines = 0;
	stack_t *stack = NULL;
	size_t size  = 0;
	FILE *fp = NULL;

	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	fp = fopen(av[1], "r");
	if (!fp)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	while (-1 != getline(&buffer, &size, fp))
	{
		number_lines++;
		token = buff_separator(buffer, "\t\n ");
		if (token != NULL)
		{
			if (execute_loop(token, number_lines, &stack) == -1)
			{
			dprintf(STDERR_FILENO, "L%d: usage: push integer\n", number_lines);
			free_everything(buffer, &stack);
			fclose(fp);
			exit(EXIT_FAILURE);
			}
		}
	}
	free_everything(buffer, &stack);
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
	unsigned int j = 0, i = 0, r = 0;
	char k = 48;

	while (array_lines[j] && j < 2)
		j++;
	if (j == 2)
	{
		if (strcmp(array_lines[0], "push") == 0)
		{
			while (array_lines[1][i] && array_lines[1][i] != '\n')
			{
				k = 48;
				if (array_lines[1][i] == '-')
				{
					i = 0;
					r++;
				}
				while (k >= 48 && k <= 57)
				{
					if (array_lines[1][i] == k)
						r++;
					k++;
				}
				i++;
			}
			if (r == i)
				_value = atoi(array_lines[1]);
			else
			{
				free(array_lines);
				return (-1);
			}
		}
	}
	if (strcmp(array_lines[0], "push") == 0 && j != 2)
		return (-1);
	if (j != 0)
		get_func(array_lines[0], stack, number_lines);
	free(array_lines);
	return (0);
}

/**
 * free_everything - function to free memory
 * @buffer: buffer
 * @stack: pointer to top
 * Return: void
 */
void free_everything(char *buffer, stack_t **stack)
{
	free_stack(stack);
	free(buffer);
}
