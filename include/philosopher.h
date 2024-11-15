/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:38:22 by marvin            #+#    #+#             */
/*   Updated: 2024/11/15 19:04:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		*threads;
	pthread_t		waiter;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	sleep_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	int				id;
	int				dead_flag;
	int				time_to_eat;
	int				last_meal;
	int				time_to_sleep;
	int				time_to_die;
	int				nb_philos;
	int				times_each_must_eat;
}					t_philo;

typedef struct s_data
{
	int				time;
	pthread_mutex_t	start_philo;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	sleep_mutex;
	pthread_mutex_t	write_mutex;
	t_philo			*philos;
}				t_data;

size_t	get_time(void);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		check_argv(int argc, char **argv);
void	free_data(t_data *data);
void	*ft_calloc(size_t n_memb, size_t size);
int		ft_usleep(size_t time);
void	philo_and_fork_assigner(t_data *data);
pthread_t	*routine(t_philo *philos);

#endif