/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:29:33 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/09/02 20:02:12 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIED 5

# define MES_EAT " is eating\n"
# define MES_EAT_LEN 11
# define MES_FORK " has taken a fork\n"
# define MES_FORK_LEN 18
# define MES_SLEEP " is sleeping\n"
# define MES_SLEEP_LEN 13
# define MES_THINK " is thinking\n"
# define MES_THINK_LEN 13
# define MES_DIED " died\n"
# define MES_DIED_LEN 6

typedef struct s_stru
{
	int				nbr_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nbr_eat;
	int				nbr_philo_done;
	long int		start_time;
	int				is_dead;
	int				extra;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	extra_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		death_thread;
}	t_stru;

typedef struct s_philo
{
	int			id;
	long int	time_of_last_meal;
	int			meals_eaten;
	pthread_t	thread;
	t_stru		*stru;
}	t_philo;

/*
** 0_utils.c
*/
int			ft_atoi(const char *s);
void		ft_putchar(char c);
void		ft_putstr(char *str);
void		ft_putnbr(int nb);

/*
** 1_error.c
*/
int			error_handling(int argc, char **argv);

/*
** 2_parsing.c
*/
void		struct_init(t_stru *stru);
void		parser(int argc, char **argv, t_stru *stru);

/*
** 3_malloc_free_philo.c
*/
void		free_all_philo(t_philo **philo, int i);
t_philo		**malloc_philo(t_philo **philo, t_stru *stru);

/*
** 4_time_handling.c
*/
long int	current_time_ms(void);
void		ft_sleep(long int time_in_ms);

/*
** 5_fork_mutex_init.c
*/
int			mutex_fork_init(t_stru *stru);
void		mutex_fork_destroy(t_stru *stru);

/*
** 6_threads_init.c
*/
int			threads_init(t_philo **philo, t_stru *stru);

/*
** 7_fork_locking.c
*/
void		unlock_fork(t_philo *philo);
void		lock_forks(t_philo *philo);

/*
** 8_routine.c
*/
void		*routine(void *casted_philo);

/*
** 9_death.c
*/
int			check_done(t_philo **philo);

/*
** 10_writing.c
*/
void		writing(int macro, t_philo *philo);

#endif
