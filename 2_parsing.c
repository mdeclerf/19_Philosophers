/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:26:23 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/09/02 19:46:47 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** ->nbr_philo_done : will be incremented every time a philo has eaten nbr_eat
->is_dead : will be used to stop the programm in case the philo have all eaten 
at least nbr_eat times or one philo died
->extra : extra variable that is used to protect the malloc of the **philo and
to make sure all the threads have been created before launching the routine
*/
void	struct_init(t_stru *stru)
{
	stru->nbr_philo = 0;
	stru->t_to_die = 0;
	stru->t_to_eat = 0;
	stru->t_to_sleep = 0;
	stru->nbr_eat = 0;
	stru->nbr_philo_done = 0;
	stru->start_time = 0;
	stru->is_dead = 0;
	stru->extra = 0;
}

void	parser(int argc, char **argv, t_stru *stru)
{
	stru->nbr_philo = ft_atoi(argv[1]);
	stru->t_to_die = ft_atoi(argv[2]);
	stru->t_to_eat = ft_atoi(argv[3]);
	stru->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		stru->nbr_eat = ft_atoi(argv[5]);
	else
		stru->nbr_eat = -1;
}
