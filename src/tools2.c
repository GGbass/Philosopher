/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:24:21 by marvin            #+#    #+#             */
/*   Updated: 2025/02/03 21:12:53 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	print_thread(t_philo *philos, int id, char *str)
{
	size_t	time;

	if (!alive_status(philos))
		return ;
	pthread_mutex_lock(philos->print);
	time = get_time() - philos->start_time;
	printf("%ld %d %s\n", time, id, str);
	pthread_mutex_unlock(philos->print);
}

int	think(t_philo *philos)
{
	if (!alive_status(philos))
		return (0);
	print_thread(philos, philos->id, PHILO_THINK);
	return (1);
}
