/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:00:00 by anadal-g          #+#    #+#             */
/*   Updated: 2025/10/28 12:26:00 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_philo *philos, t_data *data)
{
	if (philos)
		free(philos);
	destroy_mutexes(data);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
}
