#include "monty.h"
/**
 * add - adds the n value of two top elements in stack
 * @stack: Pointer to top of the stack
 * @line_number: Instruction line number
 * Return: void
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *copy = NULL;

	if (*stack == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	copy = *stack;
	if (copy->next == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	copy->next->n += (*stack)->n;
	*stack = copy->next;
	(*stack)->prev = NULL;
	free(copy);
}

/**
 * nop - Do nothing
 * @stack: Pointer to top of the stack
 * @line_number: Instruction line number
 * Return: void
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}
