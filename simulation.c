/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:00:00 by anadal-g          #+#    #+#             */
/*   Updated: 2025/10/28 12:26:14 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!is_dead(philo))
	{
		philo_eat(philo);
		if (is_dead(philo))
			break ;
		philo_sleep(philo);
		if (is_dead(philo))
			break ;
		philo_think(philo);
	}
	return (NULL);
}

int	start_simulation(t_philo *philos, t_data *data)
{
	pthread_t	monitor;
	int			i;

	if (pthread_create(&monitor, NULL, death_monitor, philos) != 0)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philosopher_routine,
				&philos[i]) != 0)
			return (1);
		i++;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (0);
}
