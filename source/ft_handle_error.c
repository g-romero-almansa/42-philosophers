/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromero- <gromero-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:00:12 by gromero-          #+#    #+#             */
/*   Updated: 2023/03/23 12:40:02 by gromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

int	ft_exit(int num)
{
	if (num == 2)
		printf ("Numero de argumentos invalido\n");
	else if (num == 1)
		printf ("Argumentos invalidos\n");
	return (1);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	ft_atoi(char *s)
{
	int		i;
	int		res;

	res = 0;
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
		res = res * 10 + (s[i++] - '0');
	return (res);
}

int	ft_handle_error(int argc, char **argv)
{
	int		i;
	int		j;

	if (argc < 5 || argc > 6)
		return (ft_exit(2));
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (ft_isdigit(argv[i][j]))
				return (ft_exit(1));
	}
	return (0);
}
