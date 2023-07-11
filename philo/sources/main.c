/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:38:01 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/07/11 13:09:00 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;
	int		count;

	i = -1;
	if (check_args(argc, argv, &data) == -1)
		return (1);
	if (alloc_and_assign(&data) == -1)
		return (2);
	init_mutex(&data);
	spawn_philos(&data);
	while (++i < data.nb_philo)
		pthread_join(data.philosophers[i].thread_id, NULL);
	while (1)
	{
		pthread_mutex_lock(&data.data_mutex);
		if (data.is_alive == 0)
		{
			pthread_mutex_unlock(&data.data_mutex);
			break ;
		}
		pthread_mutex_unlock(&data.data_mutex);
		i = -1;
		count = 0;
		while (++i < data.nb_philo)
		{
			if (data.philosophers[i].nb_of_time_eat == data.nb_times_philo_must_eat)
				count++;
			if (count == data.nb_philo)
				return (display_end_game(&data), 0);
		}
	}
	free_memory_and_mutex(&data);
	return (0);
}
