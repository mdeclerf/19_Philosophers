/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_writing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:18:28 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/09/02 20:22:39 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** printf is not used for effciency reasons and MES_SLEEP, MES_SLEEP_LEN etc
are macros defined in the .h to avoid using a ft_putstr. ft_putnbr(philo->id + 1)
because the first philo id is 0
*/
void	writing_bis(int macro, t_philo *philo)
{
	if (macro == SLEEP && philo->stru->is_dead == 0)
	{
		ft_putnbr((int)(current_time_ms() - philo->stru->start_time));
		write(1, " ", 1);
		ft_putnbr(philo->id + 1);
		write(1, MES_SLEEP, MES_SLEEP_LEN);
	}
	else if (macro == THINK && philo->stru->is_dead == 0)
	{
		ft_putnbr((int)(current_time_ms() - philo->stru->start_time));
		write(1, " ", 1);
		ft_putnbr(philo->id + 1);
		write(1, MES_THINK, MES_THINK_LEN);
	}
	else if (macro == DIED)
	{
		ft_putnbr((int)(current_time_ms() - philo->stru->start_time));
		write(1, " ", 1);
		ft_putnbr(philo->id + 1);
		write(1, MES_DIED, MES_DIED_LEN);
	}
}

void	writing(int macro, t_philo *philo)
{
	pthread_mutex_lock(&philo->stru->print_mutex);
	if (macro == FORK && philo->stru->is_dead == 0)
	{
		ft_putnbr((int)(current_time_ms() - philo->stru->start_time));
		write(1, " ", 1);
		ft_putnbr(philo->id + 1);
		write(1, MES_FORK, MES_FORK_LEN);
	}
	else if (macro == EAT && philo->stru->is_dead == 0)
	{
		ft_putnbr((int)(current_time_ms() - philo->stru->start_time));
		write(1, " ", 1);
		ft_putnbr(philo->id + 1);
		write(1, MES_EAT, MES_EAT_LEN);
	}
	if (macro == SLEEP || macro == THINK || macro == DIED)
		writing_bis(macro, philo);
	pthread_mutex_unlock(&philo->stru->print_mutex);
}
