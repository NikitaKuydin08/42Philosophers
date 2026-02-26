/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 23:59:19 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/26 20:16:23 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_if_all_ate(t_philo *philo)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	if (philo->data->nb_to_eat == -1)
		return (0);
	while (i < philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo[i].meal_lock);
		if (philo[i].nb_meals_eaten >= philo->data->nb_to_eat)
			counter++;
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
	if (counter == philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo->data->finish_simulation);
		philo->data->finished = 1;
		pthread_mutex_unlock(&philo->data->finish_simulation);
		return (1);
	}
	return (0);
}

static int	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_time() - philo->last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

static int	check_if_sm_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (philo_is_dead(&philo[i]))
		{
			print_message(&philo[i], "died");
			pthread_mutex_lock(&philo->data->finish_simulation);
			philo->data->finished = 1;
			pthread_mutex_unlock(&philo->data->finish_simulation);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (check_if_all_ate(philo) || check_if_sm_dead(philo))
			break ;
		my_usleep(1);
	}
	return (ptr);
}
