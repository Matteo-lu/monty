#include "monty.h"

/**
 * buff_separator - functio to tokenize
 * @str: string to be tokenized
 * @identificator: parser
 * Return: double pointer array
 */
char **buff_separator(char *str, char *identificator)
{
	char **array_words = NULL, *token = NULL, *ptr = NULL;
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
		;

	ptr = malloc((i + 1) * sizeof(char));
	for (i = 0; str[i] != '\0'; i++)
		ptr[i] = str[i];

	ptr[i] = '\0';
	token = strtok(ptr, identificator);
	i = 0;
	while (token != NULL)
	{
		i++;
		token = strtok(NULL, identificator);
	}
	free(ptr);
	if (i == 0)
		return (NULL);
	array_words = malloc((i + 1) * sizeof(char *));
	token = strtok(str, identificator);
	i = 0;
	while (token != NULL)
	{
		array_words[i] = token;
		i++;
		token = strtok(NULL, identificator);
	}
	array_words[i] = NULL;
	return (array_words);
}

/**
 * get_func- function selector
 * @stack: Pointer to top
 * @s: string to be compared
 * @line_number: current line
 * Return: void
 */
void get_func(char *s, stack_t **stack, unsigned int line_number)
{
	instruction_t ops[] = {
		{"push", push},
		{"pop", pop},
		{"pall", pall},
		{"pint", pint},
		{"swap", swap},
		{"nop", nop},
		{"add", add},
		{"sub", sub},
		{"div", _div},
		{"mul", mul},
		{"mod", mod},
		{NULL, NULL}
	};
	unsigned int i = 0;

	if (strncmp(s, "#", 1) == 0)
	{
		return;
	}

	while (ops[i].opcode != NULL)
	{
		if (strcmp(s, ops[i].opcode) == 0)
		{
			ops[i].f(stack, line_number);
			return;
		}
		i++;
	}
	dprintf(STDERR_FILENO, "L%d: unknown instruction %s\n", line_number, s);
	free_stack(stack);
	exit(EXIT_FAILURE);
}

/**
 * new_node - Function to create a new node
 * @value: global variable
 * Return: new node
 */
stack_t *new_node(int value)
{
	stack_t *new = NULL;

	new = malloc(sizeof(stack_t));
	new->n = value;
	new->next = NULL;
	new->prev = NULL;

	return (new);
}

/**
 * free_stack - Function to free stack
 * @stack: Pointer to top
 * Return: void
 */
void free_stack(stack_t **stack)
{
	stack_t *copy;

	copy = *stack;
	while (copy != NULL)
	{
		copy = copy->next;
		free(*stack);
		*stack = copy;
	}
}

