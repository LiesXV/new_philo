/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:38:01 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/06/15 11:58:59 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;
	// int		count;

	i = -1;
	if (check_args(argc, argv, &data) == -1)
		return (1);
	if (alloc_and_assign(&data) == -1)
		return (2);
	init_mutex(&data);
	spawn_philos(&data);
	while (++i < data.nb_philo)
		pthread_join(data.philosophers[i].thread_id, NULL);
	// while (data.is_alive)
	// {
	// 	i = -1;
	// 	count = 0;
	// 	while (data.philosophers[++i])
	// 	{
	// 		if (data.philosophers[i].nb_of_time_eat == 
	// 			data.nb_times_philo_must_eat)
	// 			count++;
	// 		if (count == data.nb_philo)
	// 			return ()
	// 	}
	// }
	free_memory_and_mutex(&data);
	return (0);
}
