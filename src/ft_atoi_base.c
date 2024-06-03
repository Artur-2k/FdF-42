#include "../inc/libft.h"

static int check_base(char *base)
{
	if (ft_strlen(base) <= 1)
		return 1;
	char c[128] = { 0 };
	while(*base)
	{
       		if (*base == '+' || *base == '-' || c[(unsigned char)*base])
			 return 1;
	       	c[(unsigned char)*base] = 1;
		base++;
	}
	return 0;
}


static int base_to_dec(char c, char *base)
{
	int i = 0;
	while(*base && c != *base)
	{
		i++;
		base++;
	}
	return i;
}
int ft_atoi_base(char *str, char *base)
{
	if (check_base(base))
		return 0;
	int sign = 1, result = 0, i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
                i++;
        while (str[i] == '+' || str[i] == '-')
        {
		if (str[i] == '-')
                	sign = -sign;
                i++;
        }
	while(str[i] && ft_strchr(base, ft_tolower(str[i])))
	{
		 result = result * ft_strlen(base) + base_to_dec(ft_tolower(str[i]), base);
		 i++;
	}
	return (result * sign);
}