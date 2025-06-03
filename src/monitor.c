/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:35:18 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/06/03 12:10:57 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->death_lock);

	// Wenn Tod bereits gesetzt ist und es keine Todesmeldung ist, nichts mehr ausgeben
	if (philo->data->death && strcmp(status, "died") != 0)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return;
	}

	// Falls wir gerade einen Tod melden, muss das trotzdem durch
	long long ts = get_time_in_ms() - philo->data->start_time;

	// Wenn es ein Todesfall ist → setze death flag
	if (strcmp(status, "died") == 0)
		philo->data->death = 1;

	pthread_mutex_unlock(&philo->data->death_lock);

	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d %s\n", ts, philo->id, status);
	pthread_mutex_unlock(&philo->data->print);
}



void	*monitor(void *arg)
{
	t_data	*data = (t_data *)arg;
	int		i;
	long long time_since_meal;

	while (1)
{
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->death_lock);
		long long now = get_time_in_ms();
		time_since_meal = now - data->philos[i].last_meal;

		if (time_since_meal > data->time_to_die)
		{
			print_status(&data->philos[i], "died");
			data->death = 1;
			pthread_mutex_unlock(&data->death_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&data->death_lock);
		i++;
	}
	usleep(500);
}
}


