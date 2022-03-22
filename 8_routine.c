/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_routine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:11:20 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/09/02 20:26:56 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** the simulation stops if a philo hasn't been eating time to die before the 
start of his last meal. The variable (one for each philo) counting the number of
meals is incremented before the sleep. If all philo ate x times, nbr_philo_done
is incremented so that the death function can exit.
*/
void	eating_routine(t_philo *philo)
{
	lock_forks(philo);
	writing(EAT, philo);
	philo->time_of_last_meal = current_time_ms();
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->stru->nbr_eat)
		philo->stru->nbr_philo_done++;
	ft_sleep(philo->stru->t_to_eat);
	unlock_fork(philo);
}

/*
** a mutex (initialized in threads_init) blocks the access to a variable (stored
in the shared struct) which counts how many threads have been created. It 
allows to  start the simulation once all philo have arrived (the first one 
waiting for the others). The time is set once all philo have arrived. 
The eating routine is then started, followed by the sleep time and think is 
written (so that the waiting time of the philo to grap two forks is actually
thinking time)
*/
void	*routine(void *casted_philo)
{
	t_philo	*philo;

	philo = (t_philo *)casted_philo;
	pthread_mutex_lock(&philo->stru->extra_mutex);
	philo->stru->extra++;
	pthread_mutex_unlock(&philo->stru->extra_mutex);
	while (philo->stru->extra < philo->stru->nbr_philo)
		ft_sleep(10);
	if (philo->stru->extra == philo->stru->nbr_philo)
	{
		philo->stru->start_time = current_time_ms();
		philo->stru->extra++;
	}
	while (1)
	{
		eating_routine(philo);
		writing(SLEEP, philo);
		ft_sleep(philo->stru->t_to_sleep);
		writing(THINK, philo);
	}
	return (NULL);
}
