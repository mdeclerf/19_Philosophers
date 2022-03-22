/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_threads_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:29:02 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/09/02 20:26:19 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** norminette purposes
*/
int	free_return(int i, t_philo **philo)
{
	free_all_philo(philo, i);
	return (-1);
}

int	loop_create(t_philo **philo, t_stru *stru, int i)
{
	void	*casted_philo;

	while (i < stru->nbr_philo)
	{
		casted_philo = (void *)philo[i];
		if (pthread_create(&philo[i]->thread,
				NULL, &routine, casted_philo) != 0)
			return (free_return(i, philo));
		ft_sleep(1);
		i++;
	}
	return (0);
}

/*
** the extra and print mutex are used in the handler function of 
(pthread_create(&philo[i]->thread, NULL, &routine, casted_philo) and to protect
the print from getting scrambled. loop_create creates philo_nbr threads and 
check_done creates one thread monitoring the death of the philo
*/
int	threads_init(t_philo **philo, t_stru *stru)
{
	int		i;

	i = 0;
	pthread_mutex_init(&stru->extra_mutex, NULL);
	pthread_mutex_init(&stru->print_mutex, NULL);
	stru->extra = 0;
	if (loop_create(philo, stru, i) == -1)
		return (-1);
	if (check_done(philo) == -1 || stru->is_dead != 0)
		return (free_return(i, philo));
	i = 0;
	while (i < stru->nbr_philo)
	{
		if (pthread_join(philo[i]->thread, NULL) != 0)
			return (free_return(i, philo));
		i++;
	}
	pthread_mutex_destroy(&stru->extra_mutex);
	pthread_mutex_destroy(&stru->print_mutex);
	return (0);
}
