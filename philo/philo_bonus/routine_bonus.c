/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhairi <abkhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:50:02 by abkhairi          #+#    #+#             */
/*   Updated: 2023/12/27 21:36:24 by abkhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*thread_controle(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (1)
	{
		sem_wait(philo->data->lock);
		if (ft_gettime() - philo->last_meal >= philo->data->t_to_die)
		{
			sem_wait(philo->data->sem_print);
			philo->data->philo_is_vive = 0;
			printf("%ld %d is dead\n",
				ft_gettime() - philo->start_time, philo->id);
			kill(0, SIGINT);
			break ;
		}
		sem_post(philo->data->lock);
		usleep(100);
	}
	return (NULL);
}

void	create_semaphoree(t_data **data)
{
	sem_unlink("/semaphor");
	sem_unlink("/sem_print");
	sem_unlink("/lock");
	(*data)->semaphor = sem_open("/semaphor", O_CREAT,
			0644, (*data)->nbr_philo);
	(*data)->sem_print = sem_open("/sem_print", O_CREAT, 0644, 1);
	(*data)->lock = sem_open("/lock", O_CREAT, 0644, 1);
}

void	create_thread_cntrl(t_philo *philo)
{
	pthread_t	thrd_control;

	pthread_create(&thrd_control, NULL, &thread_controle, philo);
	pthread_detach(thrd_control);
}

void	*rotine(t_philo *philo)
{
	create_thread_cntrl(philo);
	while (philo->data->philo_is_vive == 1)
	{
		sem_wait(philo->data->semaphor);
		printprocess("%ld %d has taken a lfork\n", philo);
		sem_wait(philo->data->semaphor);
		printprocess("%ld %d has taken a rfork\n", philo);
		printprocess("%ld %d is eating\n", philo);
		sem_wait(philo->data->lock);
		philo->last_meal = ft_gettime();
		philo->count_meal += 1;
		sem_post(philo->data->lock);
		mon_usleep(philo->data->t_to_eat, philo);
		sem_post(philo->data->semaphor);
		sem_post(philo->data->semaphor);
		printprocess("%ld %d is sleeping\n", philo);
		mon_usleep(philo->data->t_to_sleep, philo);
		printprocess("%ld %d is thinking\n", philo);
		if (philo->data->n_must_eat > 0
			&& (philo->count_meal >= philo->data->n_must_eat))
			exit(0);
	}
	return (NULL);
}

void	createe_child_process(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			exit(1);
		else if (philo[i].pid == 0)
		{
			rotine(&philo[i]);
		}
		i++;
	}
}
