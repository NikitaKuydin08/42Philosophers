/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 23:59:19 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/25 21:49:47 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_if_all_ate(t_philo *philo)
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

int	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_time() - philo->last_meal >= philo->data->time_to_die
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

int	check_if_sm_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		// pthread_mutex_lock(&philo[i].meal_lock);
		if (philo_is_dead(&philo[i]))
		{
			print_message(&philo[i], "died");
			pthread_mutex_lock(&philo->data->finish_simulation);
			philo->data->finished = 1;
			pthread_mutex_unlock(&philo->data->finish_simulation);
			// pthread_mutex_unlock(&philo[i].meal_lock);
			return (1);
		}
		// pthread_mutex_unlock(&philo[i].meal_lock);
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
		my_usleep(300);
	}
	return (ptr);
}
