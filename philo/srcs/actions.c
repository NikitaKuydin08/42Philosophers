/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:40:37 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/26 19:21:33 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		philo->left_fork_state = 1;
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		philo->right_fork_state = 1;
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo->right_fork_state = 1;
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		philo->left_fork_state = 1;
		print_message(philo, "has taken a fork");
	}
}

void	put_forks_down(t_philo *philo)
{
	philo->left_fork_state = 0;
	pthread_mutex_unlock(philo->left_fork);
	philo->right_fork_state = 0;
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	philo->nb_meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_message(philo, "is eating");
	my_usleep(philo->data->time_to_eat);
}

void	philo_thinks(t_philo *philo)
{
	long long	time_to_think;

	print_message(philo, "is thinking");
	if (philo->data->nb_philo % 2 != 0)
	{
		time_to_think = (philo->data->time_to_eat * 2)
			- philo->data->time_to_sleep;
		if (time_to_think > 0)
			my_usleep(time_to_think * 0.5);
	}
}
