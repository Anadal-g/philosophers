/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:00:00 by anadal-g          #+#    #+#             */
/*   Updated: 2024/01/15 10:00:00 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_even_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->nb_philo;
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
		return (1);
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
		return (1);
	}
	print_status(philo, "has taken a fork");
	return (0);
}

static int	take_odd_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->nb_philo;
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		return (1);
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[right_fork]);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		return (1);
	}
	print_status(philo, "has taken a fork");
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (take_even_forks(philo));
	else
		return (take_odd_forks(philo));
}