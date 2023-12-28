/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhairi <abkhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:47:58 by abkhairi          #+#    #+#             */
/*   Updated: 2023/12/23 15:12:23 by abkhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	initialisation_data(t_data *data, char **av, int ac)
{
	data->nbr_philo = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	data->n_must_eat = -1;
	data->philo_is_vive = 1;
	if (ac == 6)
		data->n_must_eat = ft_atoi(av[5]);
	create_semaphoree(&data);
}

t_philo	*initialisation_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(data->nbr_philo * sizeof(t_philo));
	if (!philo)
		return (NULL);
	while (i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].pid = -1;
		philo[i].count_meal = 0;
		philo[i].start_time = ft_gettime();
		philo[i].last_meal = ft_gettime();
		philo[i].data = data;
		i++;
	}
	return (philo);
}
