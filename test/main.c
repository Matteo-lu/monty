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
		return (EXIT_FAILURE);
	}
	buffer = malloc(letters * sizeof(char));
	if (buffer == NULL)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		return (EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		free(buffer);
		return (EXIT_FAILURE);
	}
	size = read(fd, buffer, letters);
	buffer[size] = '\0';
	array_lines = buff_separator(buffer, "\n");
	while (array_lines[i] != NULL)
	{
		number_lines = i + 1;
		execute_loop(array_lines[i], number_lines, &stack);
		/*j = 0;
		array_spaces = buff_separator(array_lines[i], " ");
		while (array_spaces[j] != NULL) j++;
		if (j == 2) _value = atoi(array_spaces[1]);
		number_lines = i + 1;
		get_func(array_spaces[0], &stack, number_lines);
		free(array_spaces);
		i++;*/
		i++;
	}
	free_stack(&stack);
	free(buffer);
	free(array_lines);
	return (0);
}

void execute_loop(char *array_lines, unsigned int number_lines, stack_t **stack)
{
	unsigned int j = 0;
	char ** array_spaces = NULL;

	array_spaces = buff_separator(array_lines, " ");
	while (array_spaces[j] != NULL)
	{
		j++;
	}
	if (j == 2)
	{
		_value = atoi(array_spaces[1]);
	}
	get_func(array_spaces[0], stack, number_lines);
	free(array_spaces);
}
