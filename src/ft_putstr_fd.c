#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	n;

	n = ft_strlen(s);
	write(fd, s, n);
}