/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:55:58 by gromero-          #+#    #+#             */
/*   Updated: 2023/03/16 11:09:27 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

long long	ft_calculate_time(void)
{
	struct timeval current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * (unsigned long)1000 + current.tv_usec / 1000);
}

long long 	ft_timediff(long long t1, long long t2)
{
	return (t2 - t1);
}

void	ft_sleep(int time)
{
	long long act;

	act = ft_calculate_time();
	while (1)
	{
		if (ft_timediff(act, ft_calculate_time()) >= (long long)time)
			break ;
		usleep(50);	
	}
}
