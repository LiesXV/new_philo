/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:38:01 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/07/11 18:24:25 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	has_eaten_enough(t_philo *philo)
{
	if (!philo->data->nb_times_philo_must_eat)
		return (0);
	if (philo->nb_of_time_eat < philo->data->nb_times_philo_must_eat)
		return (0);
	return (1);
}

int	is_dead(t_philo *philo)
{
	if (get_time() - philo->last_eat > philo->data->time_to_die)
	{
		if (!print(philo, "is dead"))
			return (0);
		return (1);
	}
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
		while (i < data->nb_philo)
		{
			if (is_dead(&data->philosophers[i]))
				return (-1);
			count += has_eaten_enough(&data->philosophers[i]);
			pthread_mutex_unlock(&data->data_mutex);
			i++;
		}
		if (count == data->nb_philo)
			return (-1);
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
	if (monitoring(&data) == -1)
	{
		pthread_mutex_lock(&data.data_mutex);
		data.is_alive = 0;
		pthread_mutex_unlock(&data.data_mutex);
	}
	while (++i < data.nb_philo)
		pthread_join(data.philosophers[i].thread_id, NULL);
	free_memory_and_mutex(&data);
	return (0);
}
