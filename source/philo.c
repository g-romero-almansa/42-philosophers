/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:25:43 by gromero-          #+#    #+#             */
/*   Updated: 2023/03/22 10:49:53 by gromero-         ###   ########.fr       */
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
	if (data->death != 1)
	{
		pthread_mutex_lock(&data->fork[i]);
		pthread_mutex_lock(&data->writting);
		printf ("%lld ms %d has taken a fork\n",
		ft_calculate_time() - data->init_time, id);
		pthread_mutex_unlock(&data->writting);
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
	if (ft_timediff(l_eat, act) > (long long)t_die)
	{
		if (cpy->death != 1)
			printf ("%lld ms %d has died\n",
				ft_calculate_time() - cpy->init_time, id);
		cpy->death = 1;
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
	while (cpy->death != 1 && (cpy->not_eat > 0 || cpy->not_eat == -1))
	{
		pthread_mutex_lock(&cpy->writting);
		if (flag == 1)
			printf ("%lld ms %d is thinking\n", ft_calculate_time() - cpy->init_time, id);
		pthread_mutex_unlock(&cpy->writting);
		if (id % 2 == 0)
			usleep (50);
		if (flag == 1)
		{
			while (ft_timediff(l_eat, ft_calculate_time()) <= cpy->t_die 
				&& (cpy->t_eat + cpy->t_sleep + (cpy->n_philo * 10)) > cpy->t_die
				&& cpy->n_philo % 2 == 1)
				usleep (50);
		}
		ft_checkdeath(l_eat, cpy->t_die, cpy, id);
		if (id == 1)
			ft_pick_fork(cpy, id, cpy->n_philo);
		else
			ft_pick_fork(cpy, id, id - 1);
		ft_pick_fork(cpy, id, id);
		ft_eatimes(cpy, id);
		l_eat = ft_calculate_time();
		ft_sleep(cpy->t_eat);
		if (id == 1)
			ft_release_fork(cpy, id, cpy->n_philo);
		else
			ft_release_fork(cpy, id, id - 1);
		if (cpy->death != 1)
		{
			pthread_mutex_lock(&cpy->writting);
			printf ("%lld ms %d is sleeping\n", ft_calculate_time() - cpy->init_time, id);
			pthread_mutex_unlock(&cpy->writting);
		}
		ft_sleep2(cpy, l_eat, id);
		flag = 1;
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
	data->death = 0;
	pthread_mutex_init(&data->writting, NULL);
	if (argc == 6)
		data->not_eat = (ft_atoi(argv[5]) + 1) * data->n_philo;
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
	data->philo = malloc(data->n_philo * sizeof(data->n_philo));
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
		pthread_create(&(data->philo[i]), NULL, ft_philo, (void *)data);
		usleep(10);
	}
	/*while (data->death == 0)
	{
		ft_checkdeath()
	}*/
	i = 0;
	while (++i <= data->n_philo)
	{
		pthread_join(data->philo[i], NULL);
		usleep(10);
	}
	free(data->philo);
	free(data->fork);
	free(data);
	return (0);
}
