/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:20:50 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/25 19:30:15 by Nikita_Kuyd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// static int	ft_isnt_digit(int argc, char **argv)
// {
// 	int	i;
// 	int	j;

// 	i = 1;
// 	while (i < argc)
// 	{
// 		j = 0;
// 		while(argv[i][j])
// 		{
// 			if (argv[i][j] < '0' || argv[i][j] > '9')
// 				return (1);
// 			else if (argv[i][j] == '-')
// 				j++;
// 			else
// 				j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	handle_msg_error(char *msg)
{
	printf("%s\n", msg);
	return (1);
}

int	validate_argv(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (handle_msg_error(USAGE));
	// if (ft_isnt_digit(argc, argv))
	// {
	// 	printf("Argument values has characters different from digits\n");
	// 	return (1);
	// }
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
