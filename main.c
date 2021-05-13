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
	int fd, size, letters = 1024;
	char *buffer = NULL, **array_lines = NULL; /***array_spaces = NULL;*/
	unsigned int number_lines = 0, i = 0; /*j = 0*/
	stack_t *stack = NULL;

	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	buffer = malloc(letters * sizeof(char));
	if (buffer == NULL)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		free(buffer);
		exit(EXIT_FAILURE);
	}
	size = read(fd, buffer, letters);
	buffer[size] = '\0';
	number_lines = count_lines(buffer);
	array_lines = buff_separator(buffer, "\n");
	while (array_lines[i] != NULL)
	{
		if (execute_loop(array_lines[i], number_lines, &stack) == -1)
		{
			dprintf(STDERR_FILENO, "L%d: usage: push integer\n", number_lines);
			free_everything(buffer, &stack, array_lines);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	free_everything(buffer, &stack, array_lines);
	return (0);
}

/**
 * execute_loop - Execution loop
 * @array_lines: pointer to arguments
 * @number_lines: current line
 * @stack: pointer to top
 * Return: 0 if success or -1 if fail
 */
int execute_loop(char *array_lines, unsigned int
number_lines, stack_t **stack)
{
	unsigned int j = 0;
	char **array_spaces = NULL;

	array_spaces = buff_separator(array_lines, " ");
	while (array_spaces[j] && j < 2)
	{
		j++;
	}
	if (j == 2)
	{
		_value = atoi(array_spaces[1]);
		if (_value == 0 && strcmp(array_spaces[1], "0") != 0)
		{
			free(array_spaces);
			return (-1);
		}
	}
	if (j != 0)
	{
		get_func(array_spaces[0], stack, number_lines);
	}
	free(array_spaces);
	return (0);
}

void free_everything(char *buffer, stack_t **stack, char **array_lines)
{
	free_stack(stack);
	free(buffer);
	free(array_lines);
}

int count_lines(char *buffer)
{
	unsigned int i = 0, count = 0;

	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '\n')
		{
			count++;
		}
	}
	return (count - 1);
}
