/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhairi <abkhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:00:22 by abkhairi          #+#    #+#             */
/*   Updated: 2023/12/23 14:56:21 by abkhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_timenow;

typedef struct s_data
{
	int				nbr_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				n_must_eat;
	int				philo_is_vive;
	pthread_mutex_t	printlock;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			start_time;
	long			last_meal;
	int				count_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*locktime_count;
	t_data			*data;
}	t_philo;

int		ft_atoi(char *str);
int		ft_isdigit(int c);
int		parsin_philo(int ac, char **av);
int		create_fork_lock(pthread_mutex_t **fork,
			pthread_mutex_t **lock, t_data *data);
long	ft_gettime(void);
int		create_threade(t_philo *philo, pthread_mutex_t *fork,
			pthread_mutex_t *lock, t_data *data);
void	mon_usleep(unsigned int time, t_philo *philo);
void	printthred(char *message, t_philo *philo);
int		check_is_vive(int i, t_philo *philo, t_data *data);
t_philo	*initialisation_philo(t_data *data, pthread_mutex_t *fork,
			pthread_mutex_t *lock);
int		detruire(pthread_mutex_t *mutex, int nbr_philo);
int		check_av5(t_philo *philo, t_data *data);
#endif