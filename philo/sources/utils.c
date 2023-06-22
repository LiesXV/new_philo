/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:51:20 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/06/19 17:00:14 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	end_simulation_by_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->is_alive)
	{
		printf("%ld %d %s\n", get_time() \
			- philo->data->init_time, philo->id + 1, "died");
	}
	philo->data->is_alive = 0;
	pthread_mutex_unlock(&philo->data->data_mutex);
}

int	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->is_alive)
	{
		printf("%ld %d %s\n", get_time() \
			- philo->data->init_time, philo->id + 1, str);
		pthread_mutex_unlock(&philo->data->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (0);
}
