/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:40:37 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/25 21:13:30 by Nikita_Kuyd      ###   ########.fr       */
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
	philo->eating = 1;
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	philo->nb_meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	my_usleep(philo->data->time_to_eat);
	philo->eating = 0;
}

void	philo_thinks(t_philo *philo)
{
	int	think_time;

	print_message(philo, "is thinking");
	if (philo->id % 2 == 0)
		think_time = philo->data->time_to_eat
			- philo->data->time_to_sleep;
	else
		think_time = (philo->data->time_to_eat * 2)
			- philo->data->time_to_sleep;
	if (think_time > 0)
		my_usleep(think_time);
}
