/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:52:51 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/06/23 18:18:03 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

enum e_errors {
	FEW_ARGS,
	TOO_ARGS,
	BAD_ARGS,
	MALLOC_ERROR
};

enum e_activites {
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DIED = 3
};

typedef struct s_philo {
	struct s_data	*data;
	pthread_t		thread_id;
	int				id;
	int				activity;
	int				nb_of_time_eat;
	long			last_eat;
	long			last_sleep;
	long			start_eating;
	int				fork;
	int				own_fork;
	int				*right_fork;
	pthread_mutex_t	*m_own_fork;
	pthread_mutex_t	*m_right_fork;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				is_alive;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_philo_must_eat;
	long			init_time;
	t_philo			*philosophers;
	int				*fork;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	data_mutex;
}				t_data;

int			think(t_philo *philo);
int			routine(t_philo *philo);
int			alloc_and_assign(t_data *data);
int			error_manager(int error);
int			check_args(int argc, char **argv, t_data *data);
void		init_mutex(t_data *data);
int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
void		join_threads(t_data *data);
int			spawn_philos(t_data *data);
long		get_time(void);
int			print(t_philo *philo, char *str);
int			display_end_game(t_data *data);
void		wait_end_simulation(t_data *data);
int			spawn_philos(t_data *data);
void		free_memory_and_mutex(t_data *data);
void		end_simulation_by_death(t_philo *philo);
void		unlock_forks_to_eat(t_philo *philo);
int			fork_gestion_with_one_meal(t_philo *philo);
void		destroy_all_mutex(t_data *data);
int			lock_forks(t_philo *philo);
void		init_forks(t_philo *philo);
int			eat(t_philo *philo);
int			sleeping(t_philo *philo);
int			think(t_philo *philo);


#endif