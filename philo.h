/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:00:00 by anadal-g          #+#    #+#             */
/*   Updated: 2024/01/15 10:00:00 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				dead;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

int			ft_atoi(const char *str);
long long	get_time(void);
void		ft_usleep(int time);
void		print_status(t_philo *philo, char *status);
int			init_data(t_data *data, int argc, char **argv);
int			init_philos(t_philo **philos, t_data *data);
int			init_mutexes(t_data *data);
void		*philosopher_routine(void *arg);
void		*death_monitor(void *arg);
int			start_simulation(t_philo *philos, t_data *data);
int			take_forks(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		cleanup(t_philo *philos, t_data *data);
void		destroy_mutexes(t_data *data);
int			is_dead(t_philo *philo);
int			all_ate_enough(t_philo *philos, t_data *data);
int			should_stop_eating(t_philo *philo);

#endif