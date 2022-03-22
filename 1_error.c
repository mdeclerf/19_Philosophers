/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:08:47 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/09/02 19:43:29 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_int(int argc, char **argv)
{
	int	i;

	i = argc - 1;
	while (i > 0)
	{
		if (ft_atoi(argv[i]) <= 0 || ft_atoi(argv[i]) > 2147483647 )
			return (-1);
		i--;
	}
	return (0);
}

int	error_handling(int argc, char **argv)
{
	if (argc != 5 && argc != 6 )
	{
		printf("Invalid number of arguments\n");
		return (-1);
	}
	if (check_int(argc, argv) == -1)
	{
		printf("Invalid arguments\n");
		return (-1);
	}
	return (0);
}
