/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:53:01 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/11 21:45:26 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

static void	signal_handler(int signum)
{
	(void)signum;
	exit(1);
}

static void	process_maker(t_data *data)
{
	int	i;
	//int	status;

	i = 0;
	//status = 0;
	signal(SIGINT, signal_handler);
	sem_wait(data->start);
	while(i < data->nb_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			philo_routine(data, i + 1);
			printf("Philosopher %d is dead\n", i + 1);
			exit(0);
		}
		else if (data->philos[i].pid < 0)
			(write(2, "Error creating process", 23), free_data(data));
		i++;
	}
	sem_post(data->start);
	i = 0;
	while(i < data->nb_philos)
	{
		if (waitpid(data->philos[i].pid, NULL, 1))
			i++;
	}
	kill(data->philos->pid, SIGKILL);
	printf("All philosophers are dead\n");
	return ;
}

static void	sema_init(t_data *data)
{
	sem_unlink("/print");
	sem_unlink("/meal");
	sem_unlink("/dead");
	sem_unlink("/forks");
	sem_unlink("/start");
	data->meal = sem_open("/meal", O_CREAT, 0644, 1);
	if (data->meal == SEM_FAILED)
		(write(2, "Error creating meal", 20), free_data(data));
	data->forks = sem_open("/forks", O_CREAT, 0644, data->nb_philos);
	if (data->forks == SEM_FAILED)
		(write(2, "Error creating forks", 20), free_data(data));
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		(write(2, "Error creating print", 20), free_data(data));
	data->start = sem_open("/start", O_CREAT, 0644, 1);
	if (data->start == SEM_FAILED)
		(write(2, "Error creating start", 19), free_data(data));
	data->dead = sem_open("/dead", O_CREAT, 0644, 1);
	if (data->dead == SEM_FAILED)
		(write(2, "Error creating dead", 19), free_data(data));
	
}

static t_data	*init_argv(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		(free_data(data), write(2, "Error creating data", 20));
	data->philos = ft_calloc(ft_atoi(argv[1]), sizeof(t_philo));
	if (!data->philos)
		(free_data(data), write(2, "Error creating philos", 21));
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = (long)ft_atoi(argv[2]);
	data->time_to_eat = (long)ft_atoi(argv[3]);
	data->time_to_sleep = (long)ft_atoi(argv[4]);
	data->finished = &data->philos->finished;
	data->philos->dead_flag = &data->dead_flag;
	if (argc == 6)
		data->times_each_must_eat = ft_atoi(argv[5]);
	else
		data->times_each_must_eat = -1;
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (!check_argv(argc, argv))
		return (0);
	data = init_argv(argc, argv);
	sema_init(data);
	process_maker(data);
	free_data(data);
	return (0);
}
