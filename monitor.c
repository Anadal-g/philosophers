/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:00:00 by anadal-g          #+#    #+#             */
/*   Updated: 2025/10/28 12:26:12 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (get_time() - philos[i].last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->dead = 1;
			pthread_mutex_unlock(&data->death_mutex);
			pthread_mutex_unlock(&data->meal_mutex);
			print_status(&philos[i], "died");
			return (1);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (0);
}

static int	check_meals_complete(t_philo *philos, t_data *data)
{
	if (data->nb_must_eat != -1 && all_ate_enough(philos, data))
	{
		pthread_mutex_lock(&data->death_mutex);
		data->dead = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	t_philo	*philos;
	t_data	*data;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (!is_dead(&philos[0]))
	{
		if (check_death(philos, data))
			return (NULL);
		if (check_meals_complete(philos, data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
