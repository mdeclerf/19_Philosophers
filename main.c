/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:35:31 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/09/02 20:25:54 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_threads_init(t_philo **philo, t_stru *stru)
{
	if (mutex_fork_init(stru) == -1)
	{
		free_all_philo(philo, stru->nbr_philo);
		free(stru);
		return (-1);
	}
	if (threads_init(philo, stru) == -1)
	{
		mutex_fork_destroy(stru);
		free(stru);
		return (-1);
	}
	return (0);
}

/*
** error check / allocation and initialization of stru / parsing / allocation
of each *philo and each philo[i] / initialization of the fork mutexs (UP) /
initialization of the threads (UP) / destruction of the fork_mutexs / free
*/
int	main(int argc, char **argv)
{
	t_philo	**philo;
	t_stru	*stru;

	philo = NULL;
	if (error_handling(argc, argv) == -1)
		return (-1);
	stru = malloc(sizeof(t_stru));
	if (!stru)
		return (-1);
	struct_init(stru);
	parser(argc, argv, stru);
	philo = malloc_philo(philo, stru);
	if (stru->extra == -1)
	{
		free(stru);
		return (-1);
	}
	if (mutex_threads_init(philo, stru) == -1)
		return (-1);
	mutex_fork_destroy(stru);
	free_all_philo(philo, stru->nbr_philo);
	free(stru);
	return (0);
}
