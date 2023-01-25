/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:25:43 by gromero-          #+#    #+#             */
/*   Updated: 2023/01/25 14:24:01 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

void	ft_release_fork(t_data *data, int i, int j)
{
	pthread_mutex_unlock(&data->fork[i]);
	pthread_mutex_unlock(&data->fork[j]);
}

void	ft_pick_fork(t_data *data, int i, int j)
{
	pthread_mutex_lock(&data->fork[i]);
	pthread_mutex_lock(&data->fork[j]);
	printf ("%ld ms %d has taken a fork\n", ft_calculate_time(data), data->i);
	printf ("%ld ms %d has taken a fork\n", ft_calculate_time(data), data->i);
}

void	*ft_philo(void	*data)
{
	t_data *cpy;

	cpy = (t_data *)data;
	printf ("%ld ms  %d is thinking.\n", ft_calculate_time(data), cpy->i);
	//while (1)
	//{
		if (cpy->i == 0)
			ft_pick_fork((t_data *)data, cpy->i, (cpy->n_philo - 1));
		else
			ft_pick_fork((t_data *)data, cpy->i, (cpy->i - 1));
		printf ("%ld ms  %d is eating.\n", ft_calculate_time(data), cpy->i);
		usleep(cpy->t_eat * 1000);
		if (cpy->i == 0)
			ft_release_fork((t_data *)data, cpy->i, (cpy->n_philo - 1));
		else
			ft_release_fork((t_data *)data, cpy->i, (cpy->i - 1));
		printf ("%ld ms  %d is sleeping.\n", ft_calculate_time(data), cpy->i);
		usleep(cpy->t_sleep * 1000);
	//}
	return (data);
}

void	ft_init(int argc, char **argv, t_data *data)
{
	data->i = -1;
	data->n_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	gettimeofday(data->init_time, NULL);
	if (argc == 6)
		data->not_eat = ft_atoi(argv[5]);
	else
		data->not_eat = 0;
}

int	main(int argc, char **argv)
{
	t_data			*data;
	
	if (ft_handle_error(argc, argv))
		return (0);
	data = malloc(sizeof(t_data));
	data->init_time = malloc(sizeof(struct timeval));
	ft_init(argc, argv, data);
	data->philo = malloc(data->n_philo * sizeof(pthread_t));
	data->fork = malloc(data->n_philo * sizeof(pthread_mutex_t));
	if (!data || !data->philo || !data->fork || !data->init_time)
		return (0);
	while (++data->i < data->n_philo)
	{
		pthread_mutex_init(&data->fork[data->i], NULL);
	}
	data->i = -1;
	while (++data->i < data->n_philo)
	{
		pthread_create(&data->philo[data->i], NULL, ft_philo, (void *)data);
		usleep(50);
	}
	data->i = -1;
	while (++data->i < data->n_philo)
	{
		pthread_join(data->philo[data->i], NULL);
	}
	free(data->init_time);
	free(data->philo);
	free(data->fork);
	free(data);
	return (0);
}
