/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:35:18 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/06/04 13:23:34 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void	*monitor(void *arg)
{
	t_data	*data = (t_data *)arg;
	int		i;

	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->death_lock);
			long long now = get_time_in_ms();

			// Warten, bis Philosophen gestartet sind
			if (data->philos[i].last_meal < data->start_time)
			{
				pthread_mutex_unlock(&data->death_lock);
				i++;
				continue;
			}

			long long time_since_meal = now - data->philos[i].last_meal;
			if (time_since_meal > data->time_to_die && !data->death)
			{
    			data->death = 1;
    			pthread_mutex_unlock(&data->death_lock);
			    pthread_mutex_lock(&data->print);
    			printf("%lld %d died\n", timestamp(data), data->philos[i].id);
    			pthread_mutex_unlock(&data->print);
			    return NULL;
			}	
			pthread_mutex_unlock(&data->death_lock);
			i++;
		}
		usleep(500);
		}
}