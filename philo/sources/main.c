/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:38:01 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/07/12 16:45:04 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	has_eaten_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_philo);
	if (!philo->data->nb_times_philo_must_eat)
		return (pthread_mutex_unlock(&philo->data_philo), 0);
	if (philo->nb_of_time_eat < philo->data->nb_times_philo_must_eat)
		return (pthread_mutex_unlock(&philo->data_philo), 0);
	pthread_mutex_unlock(&philo->data_philo);
	return (1);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_philo);
	if (get_time() - philo->last_eat > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data_philo);
		if (!print(philo, "is dead"))
			return (0);
		return (1);
	}
	pthread_mutex_unlock(&philo->data_philo);
	return (0);
}

int	monitoring(t_data	*data)
{
	int	i;
	int	count;

	while (1)
	{
		i = 0;
		count = 0;
		usleep(1000);
		while (i < data->nb_philo)
		{
			if (is_dead(&data->philosophers[i]))
				return (0);
			count += has_eaten_enough(&data->philosophers[i]);
			i++;
		}
		if (count == data->nb_philo)
			return (0);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = -1;
	if (check_args(argc, argv, &data) == -1)
		return (1);
	if (alloc_and_assign(&data) == -1)
		return (2);
	init_mutex(&data);
	spawn_philos(&data);
	usleep(10000);
	if (monitoring(&data) == 0)
	{
		pthread_mutex_lock(&data.data_mutex);
		data.is_alive = 0;
		pthread_mutex_unlock(&data.data_mutex);
	}
	while (++i < data.nb_philo)
		pthread_join(data.philosophers[i].thread_id, NULL);
	usleep(10000);
	free_memory_and_mutex(&data);
	return (0);
}
