/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:21:46 by gromero-          #+#    #+#             */
/*   Updated: 2023/03/22 10:39:58 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct s_data
{
	int				tpm;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				not_eat;
	int				death;
	pthread_t		*philo;
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

void		ft_sleep2(t_data *cpy, long l_eat, int id);

long long	ft_timediff(long long t1, long long t2);

void		ft_checkdeath(long long l_eat, int t_die, t_data *cpy, int id);

int			ft_atoi(char *s);

#endif
