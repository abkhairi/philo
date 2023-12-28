/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhairi <abkhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:48:35 by abkhairi          #+#    #+#             */
/*   Updated: 2023/12/23 15:19:55 by abkhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_number(char *av)
{
	int	i;

	i = 0;
	if (av[i] == '+')
		i++;
	while (av[i])
	{
		if (ft_isdigit(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	parsin_philo(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (0);
	if (ac == 6 && ft_atoi(av[5]) == 0)
		return (0);
	if (ft_atoi(av[1]) == 0)
		return (0);
	ac--;
	while (ac > 0)
	{
		if (ft_atoi(av[ac]) <= 0 || is_number(av[ac]) == 0)
			return (0);
		ac--;
	}
	return (1);
}

int	detruire(pthread_mutex_t *mutex, int nbr_philo)
{
	int	i;
	int	j;

	i = 0;
	while (i < nbr_philo)
	{
		j = pthread_mutex_destroy(&mutex[i]);
		if (j != 0)
		{
			printf("error destroy mutex");
			return (1);
		}
		i++;
	}
	free(mutex);
	return (0);
}
