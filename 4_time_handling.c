/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_time_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:28:04 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/09/02 19:57:17 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** int gettimeofday(struct timeval *tv, struct timezone *tz);
struct timeval {
    time_t      tv_sec; 
    suseconds_t tv_usec; } gives the current number of secondes and microseconds
this function returns the current time in miliseconds
*/
long int	current_time_ms(void)
{
	struct timeval	time;
	long int		current_time_ms;

	gettimeofday(&time, NULL);
	current_time_ms = time.tv_sec * (long)1000 + time.tv_usec / (long)1000;
	return (current_time_ms);
}

/*
** since usleep sleeps for at least asked microseconds it lacks precision
this function calls usleep in a loop to make sure it doesn't go past the 
asked sleeping time. It takes as an argument the time to sleep in 
miliseconds 
*/
void	ft_sleep(long int time_in_ms)
{
	long int	start_time;

	start_time = current_time_ms();
	while ((current_time_ms() - start_time) < time_in_ms)
		usleep(80);
}
