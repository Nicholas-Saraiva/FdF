# include "fdf.h"

t_line_node *merge_iterative(t_line_node *a, t_line_node *b)
{
	t_line_node dummy;
	t_line_node *tail = &dummy;

	dummy.next = NULL;

	while (a && b)
	{
		if (a->depth <= b->depth)
		{
			tail->next = a;
			a = a->next;
		}
		else
		{
			tail->next = b;
			b = b->next;
		}
		tail = tail->next;
	}

	tail->next = (a) ? a : b;

	return dummy.next;
}

// Função para dividir a lista em duas metades usando "fast and slow pointer"
static void split_list(t_line_node *source, t_line_node **frontRef, t_line_node **backRef)
{
	t_line_node *fast;
	t_line_node *slow;

	if (!source || !source->next)
	{
		*frontRef = source;
		*backRef = NULL;
		return;
	}

	slow = source;
	fast = source->next;

	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

// Função principal do merge sort recursivo
t_line_node *merge_sort_lines(t_line_node *head)
{
	t_line_node *front;
	t_line_node *back;

	if (!head || !head->next)
		return head;

	split_list(head, &front, &back);

	front = merge_sort_lines(front);
	back = merge_sort_lines(back);

	return merge_iterative(front, back);
}