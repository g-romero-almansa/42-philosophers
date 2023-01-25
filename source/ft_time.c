/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:55:58 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/25 13:17:17 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

long	ft_calculate_time(t_data *data)
{
	struct timeval current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000000 + current.tv_usec) - (data->init_time->tv_sec * 1000000 + data->init_time->tv_usec));
}
