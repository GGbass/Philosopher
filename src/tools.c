/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:43:46 by marvin            #+#    #+#             */
/*   Updated: 2024/11/16 23:36:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	negative;
	int	result;

	i = 0;
	negative = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || (str[i] == '+'))
	{
		if (str[i] == '-')
			negative *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (str[i] - '0') + (result * 10);
		if (result * negative > INT_MAX || result * negative < INT_MIN)
			return (printf("MAX or MIN INT exceeded"), -1);
		i++;
	}
	return (result * negative);
}

void	*ft_calloc(size_t n_memb, size_t size)
{
	void	*ptr;
	char	*tmp;
	size_t	i;

	i = 0;
	ptr = malloc(n_memb * size);
	if (!ptr)
		return (NULL);
	tmp = ptr;
	while (i < (n_memb * size))
	{
		tmp[i] = 0;
		i++;
	}
	return (ptr);
}

size_t	get_time(void)
{
	struct timeval	tv;
	size_t			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
	return (1);
}
