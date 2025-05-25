/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:00:00 by anadal-g          #+#    #+#             */
/*   Updated: 2024/01/15 10:00:00 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->death_mutex);
	dead = philo->data->dead;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (dead);
}

int	all_ate_enough(t_philo *philos, t_data *data)
{
	int	i;
	int	count;

	if (data->nb_must_eat == -1)
		return (0);
	count = 0;
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (philos[i].meals_eaten >= data->nb_must_eat)
			count++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (count == data->nb_philo);
}

int	should_stop_eating(t_philo *philo)
{
	int	should_stop;

	should_stop = 0;
	if (philo->data->nb_must_eat != -1)
	{
		pthread_mutex_lock(&philo->data->meal_mutex);
		if (philo->meals_eaten >= philo->data->nb_must_eat)
			should_stop = 1;
		pthread_mutex_unlock(&philo->data->meal_mutex);
	}
	return (should_stop);
}