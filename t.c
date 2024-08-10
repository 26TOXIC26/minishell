
#include <stdlib.h>
#include <unistd.h>

typedef struct _colectore
{
	void				*ptr;
	struct _colectore	*next;

}						t_colec;

void	del_collec(void *value)
{
	free(value);
	value = NULL;
}

void	ft_lstdelone_collec(t_colec *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del_collec(lst->ptr);
	free(lst);
	lst = NULL;
}

void	ft_lstclear_collec(t_colec **lst, void (*del)(void *))
{
	t_colec	*tmp;

	if (!lst || !del || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_collec(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}

t_colec	*ft_lstnew_collec(void *content)
{
	t_colec	*head;

	head = malloc(sizeof(t_colec));
	if (!head)
		return (NULL);
	head->ptr = content;
	head->next = NULL;
	return (head);
}

t_colec	*ft_lstlast_collec(t_colec *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_collec(t_colec **lst, t_colec *new)
{
	t_colec	*ptr_node;

	if (!new || !lst)
		return ;
	if (*lst)
	{
		ptr_node = ft_lstlast_collec(*lst);
		ptr_node->next = new;
	}
	else
		*lst = new;
}

void	ft_collectore(t_colec **data, void *ptr)
{
	t_colec	*node;
	
	node = ft_lstnew_collec(ptr);
	ft_lstadd_back_collec(data, node);
}

#include <stdio.h>
int main()
{
    // t_colec *colec;

    // colec = NULL;

    // char *env = malloc(sizeof(char *) * 4);
	// ft_collectore(&colec, env);
    // ft_lstclear_collec(&colec, del_collec);

    // char p[1024];
    // char *s;
    // s = getcwd(p, 1200);
    // printf("%s\n", p);
    char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	exit(32948);
	free(pwd);

}