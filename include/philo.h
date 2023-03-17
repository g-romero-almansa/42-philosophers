/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:21:46 by gromero-          #+#    #+#             */
/*   Updated: 2023/03/16 13:47:10 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>

typedef struct l_data
{
	int				id;
	pthread_t		t_philo;
	int				r_fork;
	int				l_fork;
	struct s_data	*data;
}	p_data;

typedef struct s_data
{
	int				tpm;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				not_eat;
	p_data			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	writting;
	long long		init_time;
}	t_data;

int			ft_handle_error(int argc, char **argv);

int			ft_isdigit(char c);

int			ft_exit(int num);

void		ft_init(int argc, char **argv, t_data *data);

void		*ft_philo(void *data);

void		ft_pick_fork(t_data *data, int id, int i);

void		ft_release_fork(t_data *data, int i, int j);

void		ft_eatimes(t_data *data, int id);

long long	ft_calculate_time(void);

void		ft_sleep(int time);

long long	ft_timediff(long long t1, long long t2);

int			ft_checkdeath(long long l_eat, int t_die, t_data *cpy, int id);

void		ft_endphilo(t_data *data);

int			ft_atoi(char *s);

#endif
