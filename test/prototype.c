#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

char **buff_separator(char *str, char *identificator);
void (*get_func(char *s))(stack_t **stack, unsigned int line_number);
void push(stack_t **stack, unsigned int line_number);
void pop(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);

int main(int ac, char **av)
{
	int fd, size, i = 0, letters = 1024;
	char *buffer = NULL, **array_lines = NULL, **array_spaces = NULL;
	unsigned int number_lines = 0;
	stack_t **stack;

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
		array_spaces = buff_separator(array_lines[i], " "); /* check memory */
		printf("linea numero: %d\n", i + 1);
		get_func(array_spaces[0]);
		free(array_spaces);
		i++;
	}
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

void (*get_func(char *s))(stack_t **stack, unsigned int line_number)
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
			printf("Entramos papá\n");
		}
		i++;
	}
	printf("No entramos :c\n");
}

void push(stack_t **stack, unsigned int line_number)
{

}

void pop(stack_t **stack, unsigned int line_number)
{

}

void pall(stack_t **stack, unsigned int line_number)
{

}
