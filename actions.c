/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:00:00 by anadal-g          #+#    #+#             */
/*   Updated: 2025/10/28 12:25:43 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (is_dead(philo) || should_stop_eating(philo))
		return ;
	if (philo->data->nb_philo == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		return ;
	}
	if (take_forks(philo) != 0)
		return ;
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->id
		% philo->data->nb_philo]);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}
