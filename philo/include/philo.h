/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 21:30:18 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/02/26 20:47:46 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

# ifndef USAGE
#  define USAGE "Usage: ./philo number_of_philos time_to_die time_to_eat \
				time_to_sleep [number_of_times_each_philosopher_must_eat]"
# endif

# ifndef NEG
#  define NEG "Error: Invalid Input"
# endif

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				nb_to_eat;

	long long		start_simulation;

	pthread_mutex_t	*forks;
	pthread_mutex_t	waiter;
	pthread_mutex_t	print;
	pthread_mutex_t	finish_simulation;

	int				finished;

}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	t_data			*data;
	int				id;
	int				nb_meals_eaten;
	long long		last_meal;
	pthread_mutex_t	meal_lock;
	int				allowed_to_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				left_fork_state;
	int				right_fork_state;
	int				eating;
	struct s_philo	*right_philo;
	struct s_philo	*left_philo;
}	t_philo;

//####### ACTIONS #######//
void		take_forks(t_philo *philo);
void		put_forks_down(t_philo *philo);
void		philo_eats(t_philo *philo);
void		philo_thinks(t_philo *philo);

//####### FT_ATOI #######//
int			ft_atoi(const char *str);

//####### UTILS #######//
long long	get_time(void);
void		print_message(t_philo *philo, char *message);
void		my_usleep(long long request_time);
int			check_if_finished(t_data *data);

//####### EXIT&FREE #######//
int			destroy_mutex(t_data *data, t_philo *philo);
int			validate_argv(int argc, char **argv);
int			create_error(void);
int			handle_msg_error(char *msg);

//####### MONITOR #######//
void		*monitor(void *ptr);

//####### INIT #######//
int			init_data(t_data *data, int argc, char **agrv);
int			init_forks(t_data *data);
int			init_philosophers(t_data *data, t_philo *philo);

//####### ROUTINE #######//
void		*philo_routine(void *philo_ptr);

#endif