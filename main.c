/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:00:00 by anadal-g          #+#    #+#             */
/*   Updated: 2024/01/15 10:00:00 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s nb_philo time_to_die time_to_eat time_to_sleep", 
			argv[0]);
		printf(" [nb_must_eat]\n");
		return (1);
	}
	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_philos(&philos, &data) != 0)
		return (1);
	if (start_simulation(philos, &data) != 0)
	{
		cleanup(philos, &data);
		return (1);
	}
	cleanup(philos, &data);
	return (0);
}