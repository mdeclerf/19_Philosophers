/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_malloc_free_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:09:01 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/09/02 19:48:59 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** this function frees each philo until i within t_philo **philo
*/
void	free_all_philo(t_philo **philo, int i)
{
	while (--i >= 0)
		free(philo[i]);
	free(philo);
}

/*
** it is in this function that the main structure is attributed to each philo 
struct
*/
t_philo	**malloc_philo(t_philo **philo, t_stru *stru)
{
	int	i;

	philo = malloc(sizeof(t_philo *) * stru->nbr_philo);
	if (!philo)
	{
		stru->extra = -1;
		return (philo);
	}
	i = 0;
	while (i < stru->nbr_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
		{
			stru->extra = -1;
			free_all_philo(philo, i);
			return (philo);
		}
		philo[i]->time_of_last_meal = 0;
		philo[i]->meals_eaten = 0;
		philo[i]->id = i;
		philo[i]->stru = stru;
		i++;
	}
	return (philo);
}
