#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

char **buff_separator(char *str, char *identificator);

int main(int ac, char **av)
{
	int fd, size, i, letters = 1024;
	char *buffer = NULL, **array_lines = NULL;

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
	for (i = 0; array_lines[i] != NULL; i++)
	{
		printf("%s", array_lines[i]);
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
		printf("%s\n", token);
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
