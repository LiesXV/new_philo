/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:53:18 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/06/19 17:25:00 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	unlock_forks_to_eat(t_philo *philo)
{
	if (philo->data->nb_philo > 1)
	{
		pthread_mutex_unlock(philo->own_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
		pthread_mutex_unlock(philo->own_fork);
}

int	lock_forks_to_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (!print(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->right_fork), 0);
	if (philo->data->nb_philo > 1)
	{
		pthread_mutex_lock(philo->own_fork);
		if (!print(philo, "has taken a fork"))
			return (unlock_forks_to_eat(philo), 0);
	}
	return (1);
}

int	lock_forks(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 1)
	{
		pthread_mutex_lock(philo->own_fork);
		if (!print(philo, "has taken a fork"))
			return (pthread_mutex_unlock(philo->own_fork), 0);
		if (philo->data->nb_philo > 1)
		{
			pthread_mutex_lock(philo->right_fork);
			if (!print(philo, "has taken a fork"))
				return (unlock_forks_to_eat(philo), 0);
		}
		return (1);
	}
	else
		return (lock_forks_to_odd(philo));
}

// int	fork_gestion_with_one_meal(t_philo *philo)
// {
// 	if (philo->data->nb_times_philo_must_eat == 1)
// 	{
// 		while (philo->time_to_wait)
// 		{
// 			philo->time = get_time();
// 			waiting(philo);
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

void	init_forks(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		philo->own_fork = &philo->data->forks[philo->id];
		philo->right_fork = NULL;
		return ;
	}
	if (philo->id < philo->data->nb_philo - 1)
	{
		philo->own_fork = &philo->data->forks[philo->id];
		philo->right_fork = &philo->data->forks[philo->id + 1];
		return ;
	}
	philo->own_fork = &philo->data->forks[philo->id];
	philo->right_fork = &philo->data->forks[0];
}
