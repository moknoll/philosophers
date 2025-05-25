/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:00:16 by mknoll            #+#    #+#             */
/*   Updated: 2025/05/25 15:53:38 by mknoll           ###   ########.fr       */
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
		philos[i].last_meal = 0;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % data->num_philos]; // Weil philosoph n-1 rechte gabel wieder 0 ist, so entseht ein Ring 
		philos[i].data = data;
		i++;
	}
	data->philos = philos;
	data->forks = forks;
}

