/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 19:45:08 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/26 19:19:21 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}

void	my_usleep(long long request_time)
{
	long long	start;
	long long	current;

	start = get_time();
	while (1)
	{
		current = get_time();
		if ((current - start) >= request_time)
			break ;
		usleep(500);
	}
}

void	print_message(t_philo *philo, char *message)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print);
	timestamp = get_time() - philo->data->start_simulation;
	if (!check_if_finished(philo->data))
		printf("%lld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->data->print);
}

int	check_if_finished(t_data *data)
{
	int	finished;

	pthread_mutex_lock(&data->finish_simulation);
	finished = data->finished;
	pthread_mutex_unlock(&data->finish_simulation);
	return (finished);
}
