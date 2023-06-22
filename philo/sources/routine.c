/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:20:45 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/06/19 17:24:02 by ibenhaim         ###   ########.fr       */
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
	while (get_time() - philo->last_eat < philo->data->time_to_sleep)
	{
		if (get_time() - philo->last_eat > philo->data->time_to_die)
			return (0);
	}
	return (1);
}

static int	eat_even(t_philo *philo)
{
	if (!lock_forks(philo))
		return (0);
	if (philo->data->nb_philo == 1)
	{
		while (get_time() - philo->last_eat < philo->data->time_to_die)
			usleep(0);
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


// static long	eating(t_philo *philo)
// {
// 	if (philo->data->nb_philo > 1)
// 	{
// 		if (!text(philo, "is thinking"))
// 			return (0);
// 	}
// 	if (philo->id % 2 == 1)
// 	{
// 		if (eat_odd(philo) == -1)
// 			return (0);
// 	}
// 	else if (philo->id % 2 == 0)
// 	{
// 		if (eat_even(philo) == -1)
// 			return (0);
// 	}
// 	philo->time = get_time();
// 	if (philo->data->nb_philo == 1)
// 		return (one_philo_management(philo));
// 	if (philo->time - philo->time_backup >= philo->data->time_to_die)
// 		return (unlock_forks_to_eat(philo), 0);
// 	philo->time_backup = philo->time;
// 	if (!text(philo, "is eating"))
// 		return (unlock_forks_to_eat(philo), 0);
// 	philo->nb_of_time_eat++;
// 	return (philo->data->time_to_eat);
// }

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
	while (get_time() - philo->start_eating < philo->data->time_to_eat)
	{
		if (get_time() - philo->last_eat >= philo->data->time_to_die)
			return (unlock_forks_to_eat(philo), 0);
	}
	unlock_forks_to_eat(philo);
	philo->nb_of_time_eat++;
	philo->last_eat = get_time();
	philo->activity = SLEEPING;
	return (1);
}
