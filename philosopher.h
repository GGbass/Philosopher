/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:38:22 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 18:38:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				nb_times_each_philo_must_eat;
	int				nb_philos;
	int				*forks;
	int				*forks_status;
	int				*forks_time

}				t_philo;


typedef struct s_data
{
	//int				nb_philos;
	//int				time_to_die;
	//int				time_to_eat;
	//int				time_to_sleep;
	//int				nb_times_each_philo_must_eat;
	t_philo			*philos;
}				t_data;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		check_argv(int argc, char **argv);
void	free_data(t_data *data);
#endif