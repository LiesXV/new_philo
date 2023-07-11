/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:12:52 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/07/11 13:42:49 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_init(&data->m_forks[i], NULL);
		printf("i : %d = %p\n", i, &data->m_forks[i]);
	}
	pthread_mutex_init(&data->data_mutex, NULL);
}

void	free_memory_and_mutex(t_data *data)
{
	destroy_all_mutex(data);
	free(data->m_forks);
	free(data->philosophers);
}

void	destroy_all_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->m_forks[i]);
	pthread_mutex_destroy(&data->data_mutex);
}
