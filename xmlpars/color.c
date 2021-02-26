#include "xml.h"

int		ft_pow(int nb, int exp)
{
	if (exp == 0)
		return (1);
	return (nb * ft_pow(nb, exp - 1));
}

int	    ft_contains(const char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

int		ft_indexof(char *s, char c)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}

int		ft_atoi_base(char *s, int base)
{
	static char	*charset = "0123456789ABCDEF";
	int			i;
	int			res;
	int			len;

	i = 0;
	if (s[i] == '0' && s[i + 1] == 'x')
		s += 2;
	while (ft_contains(charset, s[i]))
		i++;
	len = i;
	res = 0;
	i = 0;
	while (ft_contains(charset, s[i]))
	{
		res += ft_indexof(charset, s[i]) * ft_pow(base, --len);
		i++;
	}
	return (res);
}

int     get_color(char *str)
{
    char    *s;
    int     i;
    int     rus;

    i = 0;
    s = ft_strtrim(str);
    while (s[i])
    {
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] = s[i] - 32;
        i++;
    }
    if (s[0] != '#')
        rus = ft_atoi(s);
    else
        rus = ft_atoi_base(s + 1, 16);
    free(s);
    return (rus);
}