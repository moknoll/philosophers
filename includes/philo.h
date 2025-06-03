/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:51:54 by mknoll            #+#    #+#             */
/*   Updated: 2025/05/26 11:35:41 by moritzknoll      ###   ########.fr       */
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

struct	s_philo {
	int				id;
	int				meals;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
};

struct s_data {
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		start_time;
	int				death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death_lock;
	t_philo			*philos;
};

int		ft_atoi(const char *str);
void	init_philo_and_forks(t_data *data);
long	get_time_in_ms(void);
void	create_threads(t_philo *philos);
void	*philo_routine(void *arg);
void	*monitor(void *arg); 


#endif
