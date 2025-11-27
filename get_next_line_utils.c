#include "get_next_line.h"

void	ft_free_list(t_list **list, t_list *clean_node, char *clean_stash)
{
	t_last	*tmp;

	if (!*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free(list->stash);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node->stash[0])
		*list = clean_node;
	else
	{
		free(clean_stash);
		free(clean_node);
	}
}

void	ft_clean(t_list **list)
{
	char	*clean_stash;
	t_list	*clean_node;
	t_list	*last;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	last = ft_lstlast(*list);
	clean_node = malloc(sizeof(t_list));
	clean_stash = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!clean_node || !clean_stash || !last)
		return ;
	while (last->stash[i] != '\0' && last-stash[i] != '\n')
		i++;
	while (last->stash[i] != '\0' && last->stash[i++])
		clean_stash[j++] = last->stash[i];
	clean_stash[j] = '\0';
	clean_node->next = NULL;
	clean_node->stash = clean_stash;
	ft_free_list(list, clean_node, clean_stash);
}

t_list	*ft_lstlast(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_create_list(t_list **list, int fd)
{
	int		n;
	char	*buffer;

	if (!buffer)
		return ;
	while (!ft_found_newline(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		n = read(fd, buffer, BUFFER_SIZE);
		if (!n)
		{
			free (buffer);
			return ;
		}
		buffer[n] = '\0';
		ft_append(list, buffer);
	}
}
char	*ft_get_line(t_list *list)
{
	char	*str;
	
	str = malloc(sizeof(char) * ft_len_stash(list) + 1);
	if (!str)
		return (NULL);
	ft_linecpy(list, str);
}

void	ft_linecpy(t_list *list, char *str)
{
	int	i;
	int	j;

	if (NULL == list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->stash[i])
		{
			if (list->stash[i] != '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = list->stash[i++];
		}
		list = list->next;
	}
	str[j] = '\0';
}

int	ft_len_stash(t_list *list)
{
	int	i;
	int	count;
	
	count = 0;
	while (list)
	{
		i = 0;
		while (list->stash[i])
		{
			count++;
			i++;
			if (list->stash[i] == '\n')
			{
				count++;
				return (count);
			}
		}
		list = list->next;
	}
	return (count);
}

void	ft_append(t_list **list, char *stash)
{	
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	last = ft_lstlast(*list);
	if (!last)
		*list = new_node;
	else
		last->next = new_node;
	new_node->next = NULL;
	new_node->stash = buffer;
}
