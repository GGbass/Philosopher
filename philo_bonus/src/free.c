/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:03:35 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/22 17:57:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"


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
				printf("killing %d\n", data->philos[i].pid);
				kill(data->philos[i].pid, 15);
				i++;
			}
			break ;
		}
		i++;
	}
}

void	free_data(t_data *data)
{
	kill_pids(data);
	if (data->philos)
	{
		free(data->philos);
	}
	free(data);
}
