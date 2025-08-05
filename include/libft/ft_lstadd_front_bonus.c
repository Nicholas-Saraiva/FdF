/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva  <nsaraiva@student.42porto.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:23:11 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/04/16 20:19:33 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	new -> next = *lst;
	*lst = new;
}

/*#include <stdio.h>
int	main(void)
{
	//t_list **ptr_node;
	t_list	*node1;
	//t_list	*node2;
	////char	fruta[] = "ABACAXI";
	////char	bolo[] = "BOLO";
	int	x = 4242;
	//int	y = 42;

	node1 = malloc(sizeof(t_list));
	//node2 = malloc(sizeof(t_list));
	//ptr_node = malloc(sizeof(t_list *));

	*ptr_node = node1;
	node1 -> content = &x;
	node1 -> next = NULL;
	//node2 -> content =  &y;
	//node2 -> next = NULL;
	//ft_lstadd_front(ptr_node, node2);
	////printf("%s de %s\n",(char *) (*ptr_node) -> content,(char *) 
	////									(*ptr_node) -> next -> content);
	//printf("%d de %d\n", *(int *) (*ptr_node) -> content, *(int *) 
	//								(*ptr_node) -> next -> content);
	//free(node1);
	//free(node2);
	//free(ptr_node);
	
	ft_lstadd_front(NULL, node1);
}
