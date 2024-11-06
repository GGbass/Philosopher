/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:43:46 by marvin            #+#    #+#             */
/*   Updated: 2024/11/01 19:43:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
			return (-1);
		i++;
	}
	return (result * negative);
}

void	ft_calloc(size_t n_membm, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(n_memb * size);
	if (!ptr)
		return (NULL);
	while (i < n_memb * size)
		(char *)ptr[i++] = 0;
	return (ptr);
}
