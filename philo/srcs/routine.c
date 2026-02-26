/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 18:28:13 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/26 00:08:15 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
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
