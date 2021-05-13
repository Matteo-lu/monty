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

	if (stack == NULL)
		exit(EXIT_FAILURE);
	copy = *stack;
	while (copy != NULL)
	{
		printf("%d\n", copy->n);
		copy = copy->next;
	}
}

/**
 * pint - Function to print the value at the top of a stack
 * @stack: Pointer to top
 * @line_number: current line
 * Return: void
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		dprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}
/**
 * pop -Removes the top element of a stack
 * @stack: Pointer to the firts element of our stack
 * @line_number: Instruction line number
 * Return: void
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *copy = NULL;

	if (*stack == NULL)
	{
		dprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->next == NULL)
	{
		free(*stack);
		*stack = NULL;
	}
	else
	{
		copy = *stack;
		copy = copy->next;
		copy->prev = NULL;
		free(*stack);
		*stack = copy;
	}


}
/**
 * swap - swaps the top and second elements of a stack
 * @stack: Pointer to the firts element of our stack
 * @line_number: Instruction line number
 * Return: void
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *copy = NULL;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		dprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	else
	{
		copy = (*stack)->next;
		(*stack)->next = copy->next;
		(*stack)->prev = copy;
		copy->prev = NULL;
		copy->next = *stack;
		*stack = copy;
	}
}