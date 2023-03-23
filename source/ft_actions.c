/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:40:51 by gromero-          #+#    #+#             */
/*   Updated: 2023/03/23 13:06:28 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

void	ft_release_fork(t_data *cpy, int i, int j)
{
	pthread_mutex_unlock(&cpy->fork[i]);
	pthread_mutex_unlock(&cpy->fork[j]);
}

void	ft_pick_fork(t_data *cpy, int id, int i)
{
	if (cpy->death != 1)
	{
		pthread_mutex_lock(&cpy->fork[i]);
		if (cpy->death == 1)
			return ;
		pthread_mutex_lock(&cpy->writting);
		printf ("%lld ms %d has taken a fork\n",
			ft_calculate_time() - cpy->init_time, id);
		pthread_mutex_unlock(&cpy->writting);
	}
}

void	ft_eatimes(t_data *data, int id)
{
	if (data->death != 1)
	{
		pthread_mutex_lock(&data->writting);
		printf ("%lld ms %d is eating\n",
			ft_calculate_time() - data->init_time, id);
		pthread_mutex_unlock(&data->writting);
		if (data->not_eat > 0)
			data->not_eat--;
	}
}

void	ft_checkdeath(long long l_eat, int t_die, t_data *cpy, int id)
{
	long long	act;

	act = ft_calculate_time();
	if (ft_timediff(l_eat, act) > (long long)t_die && cpy->death != 1)
	{
		cpy->death = 1;
		if (cpy->n_philo != 1)
			printf ("%lld ms %d has died\n",
				ft_calculate_time() - cpy->init_time, id);
	}
}

void	ft_onephilo(t_data *cpy, long l_eat, int id)
{
	long long	act;

	act = ft_calculate_time();
	while (1)
	{
		if (cpy->death == 0)
			ft_checkdeath(l_eat, cpy->t_die, cpy, id);
		if (ft_timediff(act, ft_calculate_time()) >= (long long)cpy->t_die)
			break ;
		usleep(50);
	}
}
