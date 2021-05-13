#include "monty.h"

/**
 * push - Function to push at the top of a stack
 * @stack: Pointer to top
 * @line_number: current line
 * Return: void
 */
void push(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
	stack_t *new = NULL;

	new = new_node(_value);
	if (*stack == NULL)
	{
		new->next = *stack;
		*stack = new;
	}
	else
	{
		new->next = *stack;
		(*stack)->prev = new;
		*stack = new;
	}
}

/**
 * pall - Function to print stack
 * @stack: Pointer to top
 * @line_number: current line
 * Return: void
 */
void pall(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
	stack_t *copy = NULL;

	copy = *stack;
	while (copy != NULL)
	{
		printf("%d\n", copy->n);
		copy = copy->next;
	}
}
