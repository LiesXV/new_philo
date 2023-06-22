/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:06:19 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/06/19 17:32:02 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	display_end_game(t_data *data)
{
	if (!data->nb_times_philo_must_eat)
		return (0);
	pthread_mutex_lock(&data->data_mutex);
	printf("All philosophers have eaten at least %d times.\n", \
		data->nb_times_philo_must_eat);
	pthread_mutex_unlock(&data->data_mutex);
	return (1);
}

static void	wait_philos(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->init_time)
			break ;
		pthread_mutex_unlock(&philo->data->data_mutex);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (philo->id % 2)
		usleep(1000);
}


int	routine(t_philo *philo)
{
	if (philo->activity == THINKING)
		return (think(philo));
	else if (philo->activity == EATING)
		return (eat(philo));
	else if (philo->activity == SLEEPING)
		return (sleeping(philo));

	return (1);
}

void	*philosopher(void *carac)
{
	t_philo	*philo;

	philo = (t_philo *)carac;
	init_forks(philo);
	wait_philos(philo);
	philo->last_eat = philo->data->init_time;
	while (1)
	{
		if (!routine(philo))
			break ;
	}
	// fork_gestion_with_one_meal(philo);
	// if (philo->time_to_wait && philo->activity == EATING)
	// 	unlock_forks_to_eat(philo);
	// while (get_time() - philo->time_backup < philo->time_to_wait)
	// 	usleep(0);
	end_simulation_by_death(philo);
	return (NULL);
}

int	spawn_philos(t_data *data)
{
	int	i;

	data->init_time = 0;
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_create(&data->philosophers[i].thread_id, NULL, \
			philosopher, (void *)&data->philosophers[i]);
	}
	usleep(500);
	pthread_mutex_lock(&data->data_mutex);
	data->init_time = get_time();
	pthread_mutex_unlock(&data->data_mutex);
	return (1);
}
