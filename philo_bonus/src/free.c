/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:03:35 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/17 17:54:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

void	kill_proccesses(t_data *data)
{
	int	i;
	//int	j;
	int	status;

	i = 0;
	//j = 0;
	while (1)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			while(i < data->nb_philos)
			{
				kill(data->philos[i].pid, SIGKILL);
				i++;
			}
			break ;
		}
	}
	WIFEXITED(status);
}
void	free_proccess(t_data *data)
{
	kill(data->philos->pid, SIGKILL);
	if (data->philos)
		free(data->philos);
	free(data);
	exit(0);
}

void	free_data(t_data *data)
{

	if (data->philos->pid > 0)
		kill_proccesses(data);
	if (data->philos)
	{
		free(data->philos);
	}
	free(data);
}
