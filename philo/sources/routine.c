/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:20:45 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/07/11 13:21:52 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	think(t_philo *philo)
{
	if (!print(philo, "is thinking"))
		return (0);
	philo->activity = EATING;
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (!print(philo, "is sleeping"))
		return (0);
	philo->activity = THINKING;
	wait(philo->data->time_to_sleep);
	return (1);
}

static int	eat_even(t_philo *philo)
{
	if (!lock_forks(philo))
		return (0);
	if (philo->data->nb_philo == 1)
	{
		wait(philo->data->time_to_die);
		unlock_forks_to_eat(philo);
		return (0);
	}
	return (1);
}

static int	eat_odd(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
		usleep(500 * philo->data->nb_philo);
	if (!lock_forks(philo))
		return (0);
	return (1);
}

int	eat(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 1)
	{
		if (eat_even(philo) == 0)
			return (0);
	}
	else
	{
		if (eat_odd(philo) == 0)
			return (0);
	}
	philo->start_eating = get_time();
	if (!print(philo, "is eating"))
		return (0);
	wait(philo->data->time_to_eat);
	unlock_forks_to_eat(philo);
	philo->last_eat = get_time();
	philo->nb_of_time_eat++;
	philo->activity = SLEEPING;
	return (1);
}
