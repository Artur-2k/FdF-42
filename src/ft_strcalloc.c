#include "get_next_line.h"

char	*ft_strcalloc(size_t nitems, size_t size)
{
	char	*pstr;
	int		i;

	i = 0;
	pstr = (char *)malloc(nitems * size);
	if (pstr == NULL)
		return (NULL);
	while (nitems > 0)
	{
		pstr[i] = 0;
		i++;
		nitems--;
	}
	return (pstr);
}
