/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 18:28:13 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/25 21:14:48 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	*routine(void *philo_ptr) // TO DO routine
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)philo_ptr;
// 	if (philo->id % 2 == 0)
// 		my_usleep(1);
// 	while (check_if_finished(philo->data) == 0)
// 	{
// 		take_forks(philo);
// 		philo_eats(philo);
// 		put_forks_down(philo);
// 		print_message(philo, "is sleeping");
// 		my_usleep(philo->data->time_to_sleep);
// 		print_message(philo, "is thinking");
// 	}
// }

// void	*routine_even(void *philo_ptr)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)philo_ptr;
// 	if (philo->id % 2 == 0)
// 		my_usleep(1);
// }

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 0)
		my_usleep(philo->data->time_to_eat);
	while (!check_if_finished(philo->data))
	{
		take_forks(philo);
		philo_eats(philo);
		put_forks_down(philo);
		if (check_if_finished(philo->data))
			break ;
		print_message(philo, "is sleeping");
		my_usleep(philo->data->time_to_sleep);
		philo_thinks(philo);
	}
	return (philo_ptr);
} 
