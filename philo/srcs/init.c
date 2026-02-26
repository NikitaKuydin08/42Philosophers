/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:35:33 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/26 21:26:48 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	if (!data)
		return (1);
	if (validate_argv(argc, argv))
		return (1);
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_to_eat = ft_atoi(argv[5]);
	else
		data->nb_to_eat = -1;
	if (data->nb_philo <= 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || (argc == 6 && data->nb_to_eat < 0))
		return (handle_msg_error(NEG));
	data->start_simulation = get_time();
	data->finished = 0;
	pthread_mutex_init(&data->waiter, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->finish_simulation, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_philosophers(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].allowed_to_eat = 1;
		philo[i].nb_meals_eaten = 0;
		philo[i].last_meal = get_time();
		philo[i].eating = 0;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		pthread_mutex_init(&philo[i].meal_lock, NULL);
		philo[i].data = data;
		philo[i].eating = 0;
		philo[i].left_fork_state = 0;
		philo[i].right_fork_state = 0;
		i++;
	}
	return (0);
}
