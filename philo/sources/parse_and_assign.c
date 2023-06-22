/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_assign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:39:07 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/06/19 14:04:34 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	try_digit(int argc, char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (++j < argc)
	{
		if (argv[j][0] == '+')
			i++;
		while (argv[j][++i])
		{
			if (!(argv[j][i] >= '0' && argv[j][i] <= '9'))
				return (-1);
		}
		i = -1;
	}
	return (1);
}

int	alloc_and_assign(t_data *data)
{
	int	i;

	i = -1;
	data->philosophers = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philosophers)
		return (error_manager(MALLOC_ERROR));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		free(data->philosophers);
		return (error_manager(MALLOC_ERROR));
	}
	while (++i < data->nb_philo)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].activity = THINKING;
		data->philosophers[i].nb_of_time_eat = 0;
		data->philosophers[i].last_sleep = 0;
		data->philosophers[i].last_eat = 0;
		data->philosophers[i].data = data;
	}
	return (0);
}

static int	is_long(int argc, char **argv)
{
	if (ft_atoll(argv[1]) > INT_MAX || ft_atoll(argv[1]) < 1)
		return (-1);
	if (ft_atoll(argv[2]) > INT_MAX || ft_atoll(argv[2]) < 1)
		return (-1);
	if (ft_atoll(argv[3]) > INT_MAX || ft_atoll(argv[3]) < 1)
		return (-1);
	if (ft_atoll(argv[4]) > INT_MAX || ft_atoll(argv[4]) < 1)
		return (-1);
	if (argc == 6)
	{
		if (ft_atoll(argv[5]) > INT_MAX || ft_atoll(argv[5]) < 1)
			return (-1);
	}
	return (0);
}

int	check_args(int argc, char **argv, t_data *data)
{
	if (argc < 5)
		return (error_manager(FEW_ARGS));
	else if (argc > 6)
		return (error_manager(TOO_ARGS));
	if (try_digit(argc, argv) == -1)
		return (error_manager(BAD_ARGS));
	if (is_long(argc, argv) == -1)
		return (error_manager(BAD_ARGS));
	data->is_alive = 1;
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb_times_philo_must_eat = 0;
	if (argc == 5)
		return (printf("Launching..\n"), 1);
	data->nb_times_philo_must_eat = ft_atoi(argv[5]);
	printf("Launching.. Philosophers must eat %s times.\n", argv[5]);
	return (1);
}
