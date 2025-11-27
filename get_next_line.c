#include "get_next_line.h"

char	*get_next_line(int fd)
{	
	static t_list	*list;
	char			*next_line;

	list = NULL;
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, next_line, 0) < 0) 
		return (NULL);
	ft_create_list(&list, fd);
	if (!list)
		return (NULL);
	line = ft_get_line(list);
	ft_clean(&list)
	return (next_line);
}
