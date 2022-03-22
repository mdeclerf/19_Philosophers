/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_fork_mutex_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:28:49 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/09/02 20:00:25 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** these two functions will be called in the main before the creation of the
threads. The mutexs for the forks are stored in an array in the structure 
that all the philosphers have access to so that each philo can access his own
fork and theo ne of his neighbour.
*/
int	mutex_fork_init(t_stru *stru)
{
	int	i;

	i = 0;
	stru->fork_mutex = malloc(sizeof(pthread_mutex_t) * stru->nbr_philo);
	if (!stru->fork_mutex)
		return (-1);
	while (i < stru->nbr_philo)
	{
		pthread_mutex_init(&stru->fork_mutex[i], NULL);
		i++;
	}
	return (0);
}

void	mutex_fork_destroy(t_stru *stru)
{
	int	i;

	i = 0;
	while (i < stru->nbr_philo)
	{
		pthread_mutex_destroy(&stru->fork_mutex[i]);
		i++;
	}
	free(stru->fork_mutex);
}
