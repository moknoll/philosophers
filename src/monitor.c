/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritz <moritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:35:18 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/08/05 09:51:52 by moritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	print_status(t_data *data, int id)
{
	pthread_mutex_lock(&data->death_lock);
	data->death = 1;
	pthread_mutex_unlock(&data->death_lock);
	pthread_mutex_lock(&data->print);
	printf("%lld %d died\n", timestamp(data), id);
	pthread_mutex_unlock(&data->print);
}

void	*monitor(void *arg)
{
	t_data		*data;
	int			i;
	long long	now;
	long long	time_since_meal;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->death_lock);
			now = get_time_in_ms();
			time_since_meal = now - data->philos[i].last_meal;
			if (time_since_meal > data->time_to_die && !data->death)
			{
				pthread_mutex_unlock(&data->death_lock);
				print_status(data, data->philos[i].id);
				return (NULL);
			}
			pthread_mutex_unlock(&data->death_lock);
			i++;
		}
		if (check_all_meals_complete(data))
			return (NULL);
		usleep(500);
	}
}
