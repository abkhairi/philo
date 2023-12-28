/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhairi <abkhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:48:17 by abkhairi          #+#    #+#             */
/*   Updated: 2023/12/23 17:22:22 by abkhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_init(&data->printlock, NULL);
}

t_philo	*initialisation_philo(t_data *data, pthread_mutex_t *fork
		, pthread_mutex_t *lock)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(data->nbr_philo * sizeof(t_philo));
	if (!philo)
		return (detruire(fork, data->nbr_philo)
			, detruire(lock, data->nbr_philo), NULL);
	while (i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = &fork[i];
		philo[i].right_fork = &fork[(i + 1) % data->nbr_philo];
		philo[i].locktime_count = &lock[i];
		philo[i].count_meal = 0;
		philo[i].start_time = ft_gettime();
		philo[i].last_meal = ft_gettime();
		philo[i].data = data;
		i++;
	}
	return (philo);
}

int	initialser(t_philo **philo, t_data *data, pthread_mutex_t **lock,
		pthread_mutex_t **fork)
{
	if (create_fork_lock(&*fork, &*lock, data) == 0)
		return (printf("%s", "ERROR\n"));
	*philo = initialisation_philo(data, *fork, *lock);
	if (create_threade(*philo, *fork, *lock, data) == 0)
		return (printf("%s", "ERROR\n"));
	return (1);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*lock;
	t_data			data;
	int				i;

	i = 0;
	if (parsin_philo(ac, av) == 0)
		return (printf("ERROR PLEASE CHECK ARGUMENT"), 0);
	initialisation_data(&data, av, ac);
	if (initialser(&philo, &data, &lock, &fork) != 1)
		return (printf("%s", "ERROR\n"));
	while (1)
	{
		if (i == data.nbr_philo)
			i = 0;
		if (check_is_vive(i, philo, &data) == 0)
			return (data.philo_is_vive = 0, printf("%ld %d is dead\n",
					ft_gettime() - philo->start_time, philo->id), 0);
		if ((data.n_must_eat > 0) && (check_av5(philo, &data) == 1))
			return (0);
		i++;
	}
	return (0);
}
