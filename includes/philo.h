/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:51:54 by mknoll            #+#    #+#             */
/*   Updated: 2025/06/05 14:10:31 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct	s_philo{
	int				id;
	unsigned int	meals;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
};

struct	s_data{
	int				num_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat;
	time_t			start_time;
	int				death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
};

int			ft_atoi(const char *str);
void		init_philo_and_forks(t_data *data);
long long	get_time_in_ms(void);
void		create_threads(t_philo *philos);
void		*philo_routine(void *arg);
void		*monitor(void *arg);
long long	timestamp(t_data *data);
void		smart_usleep(t_philo *philo, long time_ms);
int			check_death(t_philo *philo);
long long	timestamp(t_data *data);
int			pick_up_fork_uneven(t_philo *philo);
void		put_down_forks(t_philo *philo);
int			pick_up_fork_even(t_philo *philo);
void		clean_up(t_data *data);

#endif
