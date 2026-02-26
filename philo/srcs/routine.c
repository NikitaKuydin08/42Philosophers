/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 18:28:13 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/26 19:51:21 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	wait_inital_delay(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			my_usleep(philo->data->time_to_eat / 10);
	}
	else
	{
		if (philo->id % 2 == 0)
			my_usleep(philo->data->time_to_eat);
		else if (philo->id == philo->data->nb_philo)
			my_usleep(philo->data->time_to_eat * 2);
	}
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	wait_inital_delay(philo);
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
