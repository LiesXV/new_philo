/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:53:18 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/07/12 16:44:21 by ibenhaim         ###   ########.fr       */
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

int	lock_second_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->m_right_fork);
		if (*philo->right_fork == 1)
		{
			if (!print(philo, "has taken a fork"))
				return (pthread_mutex_unlock(philo->m_right_fork), 0);
			*philo->right_fork = 0;
			pthread_mutex_unlock(philo->m_right_fork);
			break ;
		}
		pthread_mutex_unlock(philo->m_right_fork);
		usleep(1000);
	}
	return (1);
}

int	lock_first_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->m_own_fork);
		if (philo->own_fork == 1)
		{
			if (!print(philo, "has taken a fork"))
				return (pthread_mutex_unlock(philo->m_own_fork), 0);
			philo->own_fork = 0;
			pthread_mutex_unlock(philo->m_own_fork);
			if (philo->data->nb_philo > 1)
			{
				if (!lock_second_fork(philo))
					return (0);
				else
					break ;
			}
			else
				return (1);
		}
		pthread_mutex_unlock(philo->m_own_fork);
		usleep(1000);
	}
	return (1);
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

void	init_forks(t_data *data)
{
	int	i;

	i = data->nb_philo - 1;
	if (data->nb_philo == 1)
	{
		data->philosophers[0].m_own_fork = &data->m_forks[i];
		data->philosophers[0].own_fork = 1;
		pthread_mutex_init(&data->philosophers[0].data_philo, NULL);
		return ;
	}
	data->philosophers[i].m_own_fork = &data->m_forks[i];
	data->philosophers[i].own_fork = 1;
	pthread_mutex_init(&data->philosophers[i].data_philo, NULL);
	while (i-- > 0)
	{
		data->philosophers[i].m_own_fork = &data->m_forks[i];
		data->philosophers[i].m_right_fork = &data->m_forks[i + 1];
		data->philosophers[i].own_fork = 1;
		data->philosophers[i].right_fork = &data->philosophers[i + 1].own_fork;
		pthread_mutex_init(&data->philosophers[i].data_philo, NULL);
	}
	data->philosophers[data->nb_philo - 1].m_right_fork = &data->m_forks[0];
	data->philosophers[data->nb_philo - 1].right_fork = &data->philosophers[0].own_fork;
}
