/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:00:16 by mknoll            #+#    #+#             */
/*   Updated: 2025/06/04 11:35:46 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	allocate(t_philo **philos, pthread_mutex_t **forks, t_data *data)
{
	*philos = malloc(sizeof(t_philo) * data->num_philos);
	*forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!*philos || !*forks)
	{
		printf("Error malloc failed in init philo");
		return (0);
	}
	return (1);
}

void	init_philo_and_forks(t_data *data)
{
	t_philo			*philos;
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	if (!allocate(&philos, &forks, data))
		return ;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].last_meal = data->start_time;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % data->num_philos]; // Weil philosoph n-1 rechte gabel wieder 0 ist, so entseht ein Ring
		philos[i].data = data;
		i++;
	}
	data->philos = philos;
	data->forks = forks;
	if (pthread_mutex_init(&data->print, NULL) != 0)
		printf("Error initializing print mutex\n");
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		printf("Error initializing death_lock mutex\n");
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		printf("Error initialising meal_lock mutex\n");
}

