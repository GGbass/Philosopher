/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongarci <gongarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:31:30 by gongarci          #+#    #+#             */
/*   Updated: 2025/02/04 17:32:32 by gongarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher_bonus.h"

void	sem_assigner(t_philo *philo)
{
	philo->id = i + 1;
	philo->dead_flag = &data->dead_flag;
	philo->times_each_must_eat = data->philos->times_each_must_eat;
}