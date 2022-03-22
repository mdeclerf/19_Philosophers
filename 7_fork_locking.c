/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_fork_locking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:29:14 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/09/02 20:08:56 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** the last philosopher (-1 since the first philo's id is 0) has to take the 
fork of his right neighbour : the first one
*/
void	lock_fork_even(t_philo *philo)
{
	if (philo->id == philo->stru->nbr_philo - 1)
	{
		pthread_mutex_lock(&philo->stru->fork_mutex[philo->id]);
		writing(FORK, philo);
		pthread_mutex_lock(&philo->stru->fork_mutex[0]);
		writing(FORK, philo);
	}
	else
	{
		pthread_mutex_lock(&philo->stru->fork_mutex[philo->id]);
		writing(FORK, philo);
		pthread_mutex_lock(&philo->stru->fork_mutex[philo->id + 1]);
		writing(FORK, philo);
	}
}

void	lock_fork_odd(t_philo *philo)
{
	if (philo->id == philo->stru->nbr_philo - 1)
	{
		pthread_mutex_lock(&philo->stru->fork_mutex[0]);
		writing(FORK, philo);
		pthread_mutex_lock(&philo->stru->fork_mutex[philo->id]);
		writing(FORK, philo);
	}
	else
	{
		pthread_mutex_lock(&philo->stru->fork_mutex[philo->id + 1]);
		writing(FORK, philo);
		pthread_mutex_lock(&philo->stru->fork_mutex[philo->id]);
		writing(FORK, philo);
	}
}

/*
** if the philo id is even, the philo will first take is own fork then 
attempt to reach the one of his right neighbor. if the philo id is odd, 
the philo will first take the fork of his right neighboor before his.
If there is only philo, to prevent segfaults, since one philo cannot eat
his fork is locked and there is an infinite loop waiting for his time
to die
*/
void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->stru->nbr_philo != 1)
		lock_fork_even(philo);
	else if (philo->id % 2 == 1 && philo->stru->nbr_philo != 1)
		lock_fork_odd(philo);
	else if (philo->stru->nbr_philo == 1)
	{
		pthread_mutex_lock(&philo->stru->fork_mutex[philo->id]);
		writing(FORK, philo);
		while (1)
			ft_sleep(1);
	}
}

void	unlock_fork_bis(t_philo *philo)
{
	if (philo->id == philo->stru->nbr_philo - 1)
	{
		pthread_mutex_unlock(&philo->stru->fork_mutex[0]);
		pthread_mutex_unlock(&philo->stru->fork_mutex[philo->id]);
	}
	else
	{
		pthread_mutex_unlock(&philo->stru->fork_mutex[philo->id + 1]);
		pthread_mutex_unlock(&philo->stru->fork_mutex[philo->id]);
	}
}

void	unlock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->stru->nbr_philo != 1)
	{
		if (philo->id == philo->stru->nbr_philo - 1)
		{
			pthread_mutex_unlock(&philo->stru->fork_mutex[philo->id]);
			pthread_mutex_unlock(&philo->stru->fork_mutex[0]);
		}
		else
		{
			pthread_mutex_unlock(&philo->stru->fork_mutex[philo->id]);
			pthread_mutex_unlock(&philo->stru->fork_mutex[philo->id + 1]);
		}
	}
	else if (philo->id % 2 == 1 && philo->stru->nbr_philo != 1)
		unlock_fork_bis(philo);
}
