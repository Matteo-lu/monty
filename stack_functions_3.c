#include "monty.h"

/**
 * mod - computes the rest of the division of the second and top element.
 * @stack: Pointer to top of the stack
 * @line_number: Instruction line number
 * Return: void
 */
void mod(stack_t **stack, unsigned int line_number)
{
	stack_t *copy = NULL;

	if (*stack == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	copy = *stack;
	if (copy->next == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		dprintf(STDERR_FILENO, "L%d: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}
	copy->next->n = copy->next->n % (*stack)->n;
	*stack = copy->next;
	(*stack)->prev = NULL;
	free(copy);
}
