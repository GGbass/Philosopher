/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:38:22 by marvin            #+#    #+#             */
/*   Updated: 2025/01/29 23:01:46 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <sys/time.h>

# define PHILO_EAT "\033[1;93mis eating 🍝\033[0;39m"
# define PHILO_SLEEP "\033[1;95mis sleeping 🌙\033[0;39m"
# define PHILO_THINK "\033[1;90mis thinking 💭\033[0;39m"
# define PHILO_TAKE_FORK "\033[1;94mhas taken a fork 🍴\033[0;39m"
# define PHILO_RELEASE_FORK "\033[1;94mhas release a fork 🍴\033[0;39m"
# define PHILO_DIE "\033[1;91mdied 💀\033[0;39m"

//typedef struct s_data t_data;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*print;
	pthread_mutex_t		*meal;
	pthread_mutex_t		*dead;
	pthread_mutex_t		*start;
	int					id;
	int					*dead_flag;
	long					time_to_eat;
	long				last_meal;
	long				time_to_sleep;
	long				time_to_die;
	long				ms_to_die;
	long				start_time;
	int					nb_philos;
	int					times_each_must_eat;
}						t_philo;

typedef struct s_data
{
	int				dead_flag;
	size_t				time;
	int				nb_philos;
	pthread_mutex_t	start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
	pthread_mutex_t	dead;
	t_philo			*philos;
}				t_data;


long	get_time(void);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	print_values(t_data *data);
int		check_argv(int argc, char **argv);
void	free_data(t_data *data);
void	*ft_calloc(size_t n_memb, size_t size);
int		ft_usleep(size_t time);
void	*routine(void *philo);
int		alive_status(t_philo *philos);
void	monitor(void *philos_in);
//void	thread_values(t_data *data);
void	print_thread(t_philo *philos, int id, char *str);
int	think(t_philo *philos);
int	check_philos(t_philo *philos);

#endif