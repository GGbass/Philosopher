/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:04:00 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 19:04:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	routine(t_philo *philo)
{
	philo->id = getpid();
	printf("philo id %d\n", philo->id);
	printf("current time %ld\n", get_time());
	//printf("philo routine eating\n");
	//printf("philo routine sleeping\n");
	//printf("philo routine thinking\n");
	exit(0);
}

//void	init_mutex(t_data *data, char **argv, pthread_mutex_t *mutex)
void	init_mutex()
{
	printf("init mutex\n");
}


int	main(int argc, char **argv)
{
	t_data			*data;
	int			i;

	i = 0;
	//pthread_mutex_t	*mutex;

	if (!check_argv(argc, argv))
		return (0);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (0);
	data->philos = ft_calloc(1, sizeof(t_philo));
	if (!data->philos)
		return (free_data(data), 0);
	data->philos->nb_philos = ft_atoi(argv[1]);
	data->philos->threads = ft_calloc(data->philos->nb_philos, sizeof(pthread_t));
	if (!data->philos->threads)
		return (free_data(data), 0);
	while(i < data->philos->nb_philos)
	{
		printf("philo %d\n", i);
		pthread_create(&data->philos->threads[i], NULL, (void *)routine, NULL);
		i++;
	}
	//init_mutex(data, argv, mutex);
	//init_mutex();
	//begin philosopher routine
	//begin monitoring
	//join threads
	//destroy mutex and threads
	//printf("current time %ld\n", get_time());
	pthread_exit(NULL);
	printf("wtf");
	free_data(data);
	return (0);
}
