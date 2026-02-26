/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:16:15 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/26 19:20:35 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Philosophers with threads and mutexes

memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock

no libft allowed

Simulation ends when one of the philosopher dies, or all philosophers
ated necessary number of times
*/

#include "../include/philo.h"

int	create_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_routine,
				& philo[i]) != 0)
			return (create_error());
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (create_error());
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			philo[200];
	pthread_t		observer;

	if (init_data(&data, argc, argv) || init_forks(&data)
		|| init_philosophers(&data, philo))
		return (destroy_mutex(&data, philo));
	if (data.nb_philo == 1)
	{
		print_message(&philo[0], "has taken a fork");
		my_usleep(data.time_to_die);
		print_message(&philo[0], "died");
		return (destroy_mutex(&data, philo));
	}
	pthread_create(&observer, NULL, &monitor, philo);
	if (create_threads(philo, &data))
		return (destroy_mutex(&data, philo));
	pthread_join(observer, NULL);
	destroy_mutex(&data, philo);
	return (0);
}
