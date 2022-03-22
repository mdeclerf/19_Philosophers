/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:41:27 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/09/02 17:53:32 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t'
		|| c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (0);
	else
		return (1);
}

int	ft_atoi(const char *s)
{
	int					i;
	int					sign;
	unsigned long long	ret;

	i = 0;
	sign = 1;
	ret = 0;
	while (*s != '\0' && ft_isspace(*s) == 0)
		s++;
	if (*s != '\0' && (*s == '-' || *s == '+'))
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (s[i] != '\0' && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.'))
	{
		if (((i >= 18 || ret > 1ull << 63) && sign == 1) || s[i] == '.')
			return (-1);
		if ((i >= 18 || ret > 1ull << 63) && sign == -1)
			return (0);
		ret = (ret * 10) + (s[i] - '0');
		i++;
	}
	return (ret * sign);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		ft_putstr("2147483648");
		return ;
	}
	if (nb < 0)
		nb = nb * -1;
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar((nb % 10) + '0');
}
