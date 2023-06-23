/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:53:18 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/06/23 18:19:41 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	unlock_forks_to_eat(t_philo *philo)
{
	if (philo->data->nb_philo > 1)
	{
		pthread_mutex_lock(philo->m_right_fork);
		*philo->right_fork = 1;
		pthread_mutex_unlock(philo->m_right_fork);
		pthread_mutex_lock(philo->m_own_fork);
		philo->own_fork = 1;
		pthread_mutex_unlock(philo->m_own_fork);
	}
	else
	{
		pthread_mutex_lock(philo->m_own_fork);
		philo->own_fork = 1;
		pthread_mutex_unlock(philo->m_own_fork);
	}
}

int	lock_forks_to_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->m_right_fork);
	if (*philo->right_fork == 1)
	{
		if (!print(philo, "has taken a fork"))
			return (pthread_mutex_unlock(philo->m_right_fork), 0);
		*philo->right_fork = 0;
		pthread_mutex_unlock(philo->m_right_fork);
		if (philo->data->nb_philo > 1)
		{
			pthread_mutex_lock(philo->m_own_fork);
			if (philo->own_fork == 1)
			{
				if (!print(philo, "has taken a fork"))
					return (unlock_forks_to_eat(philo), 0);
				philo->own_fork = 0;
			}
			pthread_mutex_unlock(philo->m_own_fork);
		}
	}
	else
	{
		pthread_mutex_unlock(philo->m_right_fork);
		return (lock_forks_to_odd(philo));
	}
	return (1);
}

int	lock_forks(t_philo *philo)
{
	// if ((philo->id + 1) % 2 == 1)
	// {
	pthread_mutex_lock(philo->m_own_fork);
	if (philo->own_fork == 1)
	{
		if (!print(philo, "has taken a fork"))
			return (pthread_mutex_unlock(philo->m_own_fork), 0);
		philo->own_fork = 0;
		pthread_mutex_unlock(philo->m_own_fork);
		if (philo->data->nb_philo > 1)
		{
			pthread_mutex_lock(philo->m_right_fork);
			if (*philo->right_fork == 1)
			{
				if (!print(philo, "has taken a fork"))
					return (unlock_forks_to_eat(philo), 0);
				*philo->right_fork = 0;
			}
			pthread_mutex_unlock(philo->m_right_fork);
		}
	}
	else
	{
		pthread_mutex_unlock(philo->m_own_fork);
		return (lock_forks(philo));
	}
	return (1);
	// }
	// else
	// 	return (lock_forks_to_odd(philo));
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
		philo->m_own_fork = &philo->data->m_forks[philo->id];
		philo->own_fork = 1;
		philo->right_fork = NULL;
		printf("[philo %d] own -> %p right -> %p\n", philo->id + 1, &philo->m_own_fork, &philo->m_right_fork);
		return ;
	}
	else if (philo->id < philo->data->nb_philo - 1)
	{
		philo->m_own_fork = &philo->data->m_forks[philo->id];
		philo->m_right_fork = &philo->data->m_forks[philo->id + 1];
		philo->own_fork = 1;
		philo->right_fork = &philo->data->philosophers[philo->id + 1].own_fork;
		printf("[philo %d] own z-> %p right -> %p\n", philo->id + 1, &philo->m_own_fork, &philo->m_right_fork);
		return ;
	}
	philo->m_own_fork = &philo->data->m_forks[philo->id];
	philo->m_right_fork = &philo->data->m_forks[0];
	philo->own_fork = 1;
	philo->right_fork = &philo->data->philosophers[0].own_fork;
	printf("[philo %d] own -> %p right -> %p\n", philo->id + 1, &philo->m_own_fork, &philo->m_right_fork);
}
