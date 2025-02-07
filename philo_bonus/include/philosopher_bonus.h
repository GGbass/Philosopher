/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:49:02 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/08 00:22:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>

# define PHILO_EAT "\033[1;93mis eating 🍝\033[0;39m"
# define PHILO_SLEEP "\033[1;95mis sleeping 🌙\033[0;39m"
# define PHILO_THINK "\033[1;90mis thinking 💭\033[0;39m"
# define PHILO_TAKE_FORK "\033[1;94mhas taken a fork 🍴\033[0;39m"
# define PHILO_RELEASE_FORK "\033[1;94mhas release a fork 🍴\033[0;39m"
# define PHILO_DIE "\033[1;91mdied 💀\033[0;39m"

typedef struct s_philo
{
		
	pid_t				pid;
	int					id;
	int					*dead_flag;
	int					times_each_must_eat;
}						t_philo;

typedef struct s_data
{
	pthread_t		monitorer;
	int				dead_flag;
	int				nb_philos;
	long			time_start;
	long			last_meal;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*meal;
	sem_t			*dead;
	sem_t			*start;
	t_philo			*philos;
}				t_data;

/* argv check */
int	check_argv(int argc, char **argv);
/* free */
void	free_data(t_data *data);
/* utils */
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t n_memb, size_t size);
long	get_time(void);
int		ft_usleep(size_t time);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
/* routine */
void	print_action(t_data *data, int id, char *str);
void	*philo_routine(t_data *data);

#endif