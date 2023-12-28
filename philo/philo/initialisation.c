/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhairi <abkhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:18:23 by abkhairi          #+#    #+#             */
/*   Updated: 2023/12/20 14:43:00 by abkhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_is_vive(int i, t_philo *philo, t_data *data)
{
	pthread_mutex_lock(philo[i].locktime_count);
	if (ft_gettime() - philo[i].last_meal >= (unsigned int)data->t_to_die)
		return (0);
	pthread_mutex_unlock(philo[i].locktime_count);
	return (1);
}

pthread_mutex_t	*initialiser_mutex_fork(int nbr_philo)
{
	int				i;
	pthread_mutex_t	*arry;

	arry = malloc(nbr_philo * sizeof(pthread_mutex_t));
	if (!arry)
		return (NULL);
	i = 0;
	while (i < nbr_philo)
		pthread_mutex_init(&arry[i++], NULL);
	return (arry);
}

pthread_mutex_t	*initialiser_mutex_lock(int nbr_philo)
{
	int				i;
	pthread_mutex_t	*arry;

	i = 0;
	arry = malloc(nbr_philo * sizeof(pthread_mutex_t));
	if (!arry)
		return (NULL);
	while (i < nbr_philo)
		pthread_mutex_init(&arry[i++], NULL);
	return (arry);
}

int	create_fork_lock(pthread_mutex_t **fork, pthread_mutex_t **lock
					, t_data *data)
{
	*fork = initialiser_mutex_fork(data->nbr_philo);
	if (!*fork)
		return (0);
	*lock = initialiser_mutex_lock(data->nbr_philo);
	if (!*lock)
		return (detruire(*fork, data->nbr_philo), 0);
	return (1);
}
