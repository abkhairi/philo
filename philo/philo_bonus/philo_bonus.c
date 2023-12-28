/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhairi <abkhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:49:11 by abkhairi          #+#    #+#             */
/*   Updated: 2023/12/27 21:08:47 by abkhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printprocess(char *message, t_philo *philo)
{
	sem_wait(philo->data->sem_print);
	printf(message, ft_gettime() - philo->start_time, philo->id);
	sem_post(philo->data->sem_print);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data	data;
	int		i;

	if (parsin_philo(ac, av) == 0)
		return (printf("ERROR PLEASE CHECK ARGUMENT"), 0);
	initialisation_data(&data, av, ac);
	philo = initialisation_philo(&data);
	createe_child_process(philo, &data);
	i = 0;
	while (i < data.nbr_philo)
	{
		waitpid(philo[i].pid, NULL, 0);
		i++;
	}
	free(philo);
	sem_close(data.semaphor);
	sem_close(data.sem_print);
	sem_close(data.lock);
	sem_unlink("/semaphor");
	sem_unlink("/sem_print");
	sem_unlink("/lock");
	return (0);
}
