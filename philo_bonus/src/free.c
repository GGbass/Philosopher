/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:03:35 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/13 22:22:30 by gongarci         ###   ########.fr       */
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
		}
	}
}

void	free_data(t_data *data)
{
	int i;

	i = 0;
	if (data->philos)
	{
		while (i < data->nb_philos)
		{
			free(data->philos);
			i++;
		}
		free(data->philos);
	}
	kill_proccesses(data);
	free(data->philos);
	free(data);
}
