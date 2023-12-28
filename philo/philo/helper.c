/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhairi <abkhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:08:00 by abkhairi          #+#    #+#             */
/*   Updated: 2023/12/23 14:52:25 by abkhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

void	ft_atoi_err(void)
{
	write(1, "Error\n", 6);
	exit(1);
}

int	ft_atoi(char *str)
{
	int		i;
	long	nombre;
	int		signe;

	signe = 1;
	nombre = 0;
	i = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-' || str[i] == '+') && (str[i] != '\0'))
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && (str[i] != '\0'))
	{
		nombre = nombre * 10 +(str[i] - '0');
		i++;
		if (nombre > INT_MAX)
			ft_atoi_err();
		if (nombre < INT_MIN)
			ft_atoi_err();
	}
	return ((int)nombre * signe);
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	else
		return (0);
}

long	ft_gettime(void)
{
	t_timenow	time1970;
	long		time1;
	long		time2;
	long		time;

	gettimeofday(&time1970, NULL);
	time1 = (time1970.tv_sec * 1000);
	time2 = (time1970.tv_usec / 1000);
	time = time1 + time2;
	return (time);
}

void	mon_usleep(unsigned int time, t_philo *philo)
{
	unsigned long	start;

	start = ft_gettime();
	while (philo->data->philo_is_vive == 1)
	{
		if (ft_gettime() - start < time)
			usleep(10);
		else
			break ;
	}
}
