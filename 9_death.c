/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_death.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:29:25 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/09/02 20:19:45 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** two things checked here : the death and the number of times eating for each
philo. If there is only one philo, the time_of_last_meal will be the current
time in mili seconds (so > die) and another condition applies : the start_time
to check if all philo are done eating, we compare the nbr_philo_done with the
total number of philo (incremented in the eating_routine)
*/
int	time_death(t_philo **philo, int nbr, long int die, int i)
{
	if ((current_time_ms() - philo[i]->time_of_last_meal) > die)
	{
		if (nbr != 1 && philo[i]->time_of_last_meal != 0)
		{
			philo[i]->stru->is_dead++;
			writing(DIED, philo[i]);
			return (-1);
		}
		else if (nbr == 1)
		{
			if ((current_time_ms() - philo[i]->stru->start_time) > die)
			{
				philo[i]->stru->is_dead++;
				writing(DIED, philo[i]);
				return (-1);
			}
		}
	}
	if (philo[i]->stru->nbr_philo_done == nbr)
	{
		philo[i]->stru->is_dead++;
		return (-1);
	}
	return (0);
}

/*
** the reattribution of nbr and die is meant for line length reasons. The thread
has an infinite loop that loops on each philo to check stru->is_dead 
(that will be incremented if a philo dies or if they are all done eating)
*/
void	*stop_routine(void *casted_philo)
{
	t_philo		**philo;
	int			nbr;
	long int	die;
	int			i;

	philo = (t_philo **)casted_philo;
	nbr = philo[0]->stru->nbr_philo;
	die = philo[0]->stru->t_to_die;
	while (1)
	{
		i = 0;
		while (i < nbr)
		{
			if ((time_death(philo, nbr, die, i)) == -1)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

/*
** this function creates a thread that will run in parallel with all
the threads of the philo and check if one died or if they are done
eating 
*/
int	check_done(t_philo **philo)
{
	void	*casted_philo_death;

	casted_philo_death = (void *)philo;
	if (pthread_create(&philo[0]->stru->death_thread, NULL,
			&stop_routine, casted_philo_death) != 0)
		return (-1);
	if (pthread_join(philo[0]->stru->death_thread, NULL) != 0)
		return (-1);
	else
		return (0);
}
