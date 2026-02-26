/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:20:50 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/26 20:58:25 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_not_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	handle_msg_error(char *msg)
{
	printf("%s\n", msg);
	return (1);
}

int	validate_argv(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (handle_msg_error(USAGE));
	if (is_not_digit(argc, argv))
		return (handle_msg_error(NEG));
	(void)argv;
	return (0);
}

int	create_error(void)
{
	write(2, "Error: creation of thread failed\n", 33);
	return (1);
}

int	destroy_mutex(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&philo[i].meal_lock);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->waiter);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->finish_simulation);
	return (1);
}
