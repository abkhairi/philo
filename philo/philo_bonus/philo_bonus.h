/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhairi <abkhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:49:42 by abkhairi          #+#    #+#             */
/*   Updated: 2023/12/27 21:08:36 by abkhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

typedef struct timeval	t_timenow;

typedef struct s_data
{
	int		nbr_philo;
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		n_must_eat;
	int		philo_is_vive;
	sem_t	*semaphor;
	sem_t	*sem_print;
	sem_t	*lock;
}	t_data;

typedef struct s_philo
{
	int		id;
	long	start_time;
	long	last_meal;
	int		count_meal;
	pid_t	pid;
	t_data	*data;
}	t_philo;

int		ft_atoi(char *str);
int		ft_isdigit(int c);
int		parsin_philo(int ac, char **av);
long	ft_gettime(void);
void	mon_usleep(unsigned int time, t_philo *philo);
void	printthred(char *message, t_philo *philo);
int		check_is_vive(int i, t_philo *philo, t_data *data);
int		check_av5(t_philo *philo, t_data *data);
void	create_semaphoree(t_data **data);
t_philo	*initialisation_philo(t_data *data);
void	initialisation_data(t_data *data, char **av, int ac);
void	createe_child_process(t_philo *philo, t_data *data);
void	printprocess(char *message, t_philo *philo);
#endif