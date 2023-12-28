/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhairi <abkhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:52:49 by abkhairi          #+#    #+#             */
/*   Updated: 2023/12/28 14:03:57 by abkhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_av5(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (philo[i].count_meal < data->n_must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	printthred(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->printlock);
	if (philo->data->philo_is_vive == 1)
		printf(message, ft_gettime() - philo->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->printlock);
}

static	void	take_lf_rf_eat_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printthred("%ld %d has taken a lfork\n", philo);
	pthread_mutex_lock(philo->right_fork);
	printthred("%ld %d has taken a rfork\n", philo);
	printthred("%ld %d is eating\n", philo);
	pthread_mutex_lock(philo->locktime_count);
	philo->last_meal = ft_gettime();
	philo->count_meal += 1;
	pthread_mutex_unlock(philo->locktime_count);
	mon_usleep(philo->data->t_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	printthred("%ld %d is sleeping\n", philo);
	mon_usleep(philo->data->t_to_sleep, philo);
	printthred("%ld %d is thinking\n", philo);
}

void	*routinefunc(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (philo->data->nbr_philo == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			printthred("%ld %d has taken a lfork\n", philo);
			mon_usleep(philo->data->t_to_die, philo);
		}
		if (philo->data->nbr_philo > 1)
			take_lf_rf_eat_sleep_think(philo);
	}
	return (NULL);
}

int	create_threade(t_philo *philo, pthread_mutex_t *fork,
	pthread_mutex_t *lock, t_data *data)
{
	pthread_t	*threade;
	int			i;

	threade = malloc(philo->data->nbr_philo * sizeof(pthread_t));
	if (!threade)
		return (detruire(fork, data->nbr_philo),
			detruire(lock, data->nbr_philo), free(philo), 0);
	i = 0;
	while (i < philo->data->nbr_philo)
	{
		pthread_create(&threade[i], NULL, &routinefunc, &philo[i]);
		i++;
	}
	i = 0;
	while (i < philo->data->nbr_philo)
	{
		pthread_detach(threade[i]);
		i++;
	}
	free(threade);
	return (1);
}
