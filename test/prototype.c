#include "header.h"

int _value;

int main(/*int ac, char **av*/)
{
	int ac = 2;
	char *av[2];
	int fd, size, letters = 1024;
	char *buffer = NULL, **array_lines = NULL, **array_spaces = NULL;
	unsigned int number_lines = 0, i = 0, j = 0;
	stack_t *stack = NULL;

	av[0] = "./monty";
	av[1] = "bytecodes/00.m";
	buffer = malloc(letters * sizeof(char));
	if(buffer == NULL)
	{
		perror("Error: malloc failed");
		return (EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error: Can't open file");
		return (EXIT_FAILURE);
	}
	size = read(fd, buffer, letters);
	buffer[size] = '\0';

	array_lines = buff_separator(buffer, "\n");
	while (array_lines[i] != NULL)
	{
		j = 0;
		array_spaces = buff_separator(array_lines[i], " "); /* check memory */
		while (array_spaces[j] != NULL)
		{
			j++;
		}
		if (j == 2)
		{	
			_value = atoi(array_spaces[1]);
		}
		printf("numero de palabras: %d\n", j);
		get_func(array_spaces[0], &stack, (i + 1));
		free(array_spaces);
		i++;
	}
	free_stack(&stack);
	free(buffer);
	free(array_lines);
	return (0);
}

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

void get_func(char *s, stack_t **stack, unsigned int line_number)
{
	instruction_t ops[] = {
		{"push", push},
		{"pop", pop},
		{"pall", pall},
		{NULL, NULL}
	};
	int i = 0;

	while (ops[i].opcode != NULL)
	{
		if (strncmp(s, ops[i].opcode, strlen(ops[i].opcode)) == 0)
		{
			ops[i].f(stack, line_number);
		}
		i++;
	}
	printf("No entramos :c\n");
}

void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new = NULL;

	printf("Ay gonorrea!, entramos\n");
	new = new_node(_value);
	if (*stack == NULL)
	{
		new->next = *stack;
		*stack = new;
		printf("%d pushed to stack\n", new->n);
	}
	else
	{
		new->next = *stack;
		(*stack)->prev = new;
		*stack = new;
		 printf("%d pushed to stack\n", new->n);
	}
}

void pop(stack_t **stack, unsigned int line_number)
{
	
}

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *copy = NULL;

	copy = *stack;
	while (copy != NULL)
	{
		printf("valor [%d]: %d\n", line_number, copy->n);
		copy = copy->next;
	}
}

stack_t* new_node(int value)
{
	stack_t *new = NULL;

	new = malloc(sizeof(stack_t));
	new->n = value;
	new->next = NULL;
	new->prev = NULL;

	return (new);
}

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
