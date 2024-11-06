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

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	pthreat_mutex_t	*forks;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (0);
	data->philos = ft_calloc(1, sizeof(t_philo));
	if (!data->philos)
		return (free_data(data), 0);
	return (0);
}
