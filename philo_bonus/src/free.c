/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:03:35 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/24 20:44:23 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

static void	free_sems(t_data *data)
{
	if (sem_close(data->forks) == -1)
		(write(2, "Error close fork\n", 17));
	if (sem_close(data->print) == -1)
		(write(2, "Error close print\n", 18));
	if (sem_close(data->start) == -1)
		(write(2, "Error close start\n", 18));
	if (sem_close(data->dead) == -1)
		(write(2, "Error close dead\n", 17));
	if (sem_close(data->meal) == -1)
		(write(2, "Error close meal\n", 17));
	if (sem_unlink("/forks") == -1)
		(write(2, "Error unlink fork\n", 18));
	if (sem_unlink("/print") == -1)
		(write(2, "Error unlink print\n", 19));
	if (sem_unlink("/start") == -1)
		(write(2, "Error unlink start\n", 19));
	if (sem_unlink("/dead") == -1)
		(write(2, "Error unlink dead\n", 18));
	if (sem_unlink("/meal") == -1)
		(write(2, "Error unlink meal\n", 18));
}

void	kill_pids(t_data *data)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < data->nb_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < data->nb_philos)
			{
				kill(data->philos[i].pid, 15);
				i++;
			}
			break ;
		}
		i++;
	}
}

void	free_pid_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->philos)
	{
		while (i < data->nb_philos)
		{
			free(data[i].philos);
			i++;
		}
		free(data->philos);
	}
	if (data->forks)
		free(data->forks);
	if (data->print)
		free(data->print);
	if (data->start)
		free(data->start);
	if (data->dead)
		free(data->dead);
	if (data->meal)
		free(data->meal);
	if (data)
		free(data);
}

void	free_data(t_data *data)
{
	kill_pids(data);
	if (data->philos)
	{
		free(data->philos);
	}
	free_sems(data);
	if (data)
		free(data);
}
