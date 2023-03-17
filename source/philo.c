/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:25:43 by gromero-          #+#    #+#             */
/*   Updated: 2023/03/16 13:49:29 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

void	ft_release_fork(t_data *data, int i, int j)
{
	pthread_mutex_unlock(&data->fork[i]);
	pthread_mutex_unlock(&data->fork[j]);
}

void	ft_pick_fork(t_data *data, int id, int i)
{
	pthread_mutex_lock(&data->fork[i]);
	printf ("%lld ms %d has taken a fork %d\n", ft_calculate_time() - data->init_time, id, i);
}

void	ft_eatimes(t_data *data, int id)
{
	printf ("%lld ms %d is eating\n", ft_calculate_time() - data->init_time, id);
	data->not_eat--;
}

int	ft_checkdeath(long long l_eat, int t_die, t_data *cpy, int id)
{
	long long act;

	act = ft_calculate_time();
	if (ft_timediff(l_eat, act) >= (long long)t_die)
	{
		printf ("%lld ms %d has died\n", ft_calculate_time() - cpy->init_time, id);
		return (1);
	}
	return (0);
}

void	ft_endphilo(t_data *data)
{
	int		i;

	i = 0;
	while (++i <= data->n_philo)
	{
		pthread_join(data->philo[i].t_philo, NULL);
		usleep(50);
	}
	i = 0;
	while (++i <= data->n_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
	}
}

void	*ft_philo(void	*data)
{
	t_data		*cpy;
	int			id;
	long		l_eat;
	int			flag;

	cpy = (t_data *)data;
	id = cpy->tpm;
	l_eat = ft_calculate_time();
	flag = 0;
	if (cpy->n_philo == 1)
	{
		printf ("%lld ms %d has died\n", ft_calculate_time() - cpy->init_time, id);
		return (data);
	}
	if (cpy->not_eat >= 0)
	{
		while (cpy->not_eat >= 0)
		{
			if (ft_calculate_time() - l_eat > cpy->t_die)
			{
				printf ("%lld ms %d has died\n", ft_calculate_time() - cpy->init_time, id);
				return (data);
			}
			if (flag == 1)
				printf ("%lld ms %d is thinking\n", ft_calculate_time() - cpy->init_time, id);
			if (id % 2 == 1)
			{
				ft_pick_fork(cpy, id, id);
				if (id == cpy->n_philo)
					ft_pick_fork(cpy, id, 1);
				else
					ft_pick_fork(cpy, id, id - 1);
			}
			else if (id % 2 == 0)
			{
				if (id == cpy->n_philo)
					ft_pick_fork(cpy, id, 1);
				else
					ft_pick_fork(cpy, id, id - 1);
				ft_pick_fork(cpy, id, id);
			}
			ft_eatimes(cpy, id);
			usleep(1000 * cpy->t_eat);
			if (id == cpy->n_philo)
				ft_release_fork(cpy, id, 1);
			else
				ft_release_fork(cpy, id, id - 1);
			l_eat = ft_calculate_time();
			printf ("%lld ms %d is sleeping\n", ft_calculate_time() - cpy->init_time, id);
			usleep(1000 * cpy->t_sleep);
			flag = 1;
		}	
	}
	else
	{
		while (1)
		{
			if (ft_checkdeath(l_eat, cpy->t_die, cpy, id) == 1)
			{
				pthread_mutex_lock(&cpy->writting);
				return (data);
			}
			if (flag == 1)
				printf ("%lld ms %d is thinking\n", ft_calculate_time() - cpy->init_time, id);
			if (id % 2 == 1)
			{
				if (id == 1)
					ft_pick_fork(cpy, id, cpy->n_philo);
				else
					ft_pick_fork(cpy, id, id - 1);
				ft_pick_fork(cpy, id, id);
			}
			else if (id % 2 == 0)
			{
				ft_pick_fork(cpy, id, id);
				if (id == 1)
					ft_pick_fork(cpy, id, cpy->n_philo);
				else
					ft_pick_fork(cpy, id, id - 1);
			}
			if (ft_checkdeath(l_eat, cpy->t_die, cpy, id) == 1)
				return (data);
			ft_eatimes(cpy, id);	
			ft_sleep(cpy->t_eat);
			if (id == 1)
				ft_release_fork(cpy, id, cpy->n_philo);
			else
				ft_release_fork(cpy, id, id - 1);
			l_eat = ft_calculate_time();
			if (ft_checkdeath(l_eat, cpy->t_die, cpy, id) == 1)
				return (data);
			printf ("%lld ms %d is sleeping\n", ft_calculate_time() - cpy->init_time, id);
			ft_sleep(cpy->t_sleep);
			flag = 1;
		}
	}
	return (data);
}

void	ft_init(int argc, char **argv, t_data *data)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->init_time = ft_calculate_time();
	pthread_mutex_init(&data->writting, NULL);
	if (argc == 6)
		data->not_eat = ft_atoi(argv[5]) * data->n_philo;
	else
		data->not_eat = -1;
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if (ft_handle_error(argc, argv))
		return (0);
	data = malloc(sizeof(t_data));
	ft_init(argc, argv, data);
	data->philo = malloc(data->n_philo * sizeof(p_data));
	data->fork = malloc(data->n_philo * sizeof(pthread_mutex_t));
	if (!data || !data->philo || !data->fork)
		return (0);
	i = 0;
	while (++i <= data->n_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
	}
	i = 0;
	while (++i <= data->n_philo)
	{
		data->tpm = i;
		pthread_create(&(data->philo[i].t_philo), NULL, ft_philo, (void *)data);
		usleep(10);
	}
	i = 0;
	while (++i <= data->n_philo)
	{
		pthread_join(data->philo[i].t_philo, NULL);
		//usleep(50);
	}
	free(data->philo);
	free(data->fork);
	free(data);
	return (0);
}
