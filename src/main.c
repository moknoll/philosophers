/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:57:30 by mknoll            #+#    #+#             */
/*   Updated: 2025/06/03 11:53:06 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// clean up data() --> also destroy mutexes and free everything
// start threads


t_data	*get_data(char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("error malloc failed in get_data\n");
		return (NULL);
	}
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	return (data);
}
int main(int argc, char *argv[])
{
	t_data *data;
	pthread_t monitor_thread;
	int i;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s num_philos time_to_die time_to_eat time_to_sleep [must_eat]\n", argv[0]);
		return (1);
	}

	data = get_data(argv);
	if (!data)
		return (1);

	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;

	init_philo_and_forks(data);
	data->start_time = get_time_in_ms();

	// Philosophen-Threads starten
	for (i = 0; i < data->num_philos; i++)
	{
		data->philos[i].last_meal = get_time_in_ms();
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
		{
			printf("Error creating philosopher thread %d\n", i + 1);
			return (1);
		}
	}

	// Monitor-Thread starten
	if (pthread_create(&monitor_thread, NULL, monitor, data) != 0)
	{
		printf("Error creating monitor thread\n");
		return (1);
	}

	// Auf Philosophen-Threads warten
	for (i = 0; i < data->num_philos; i++)
		pthread_join(data->philos[i].thread, NULL);

	// Auf Monitor-Thread warten
	pthread_join(monitor_thread, NULL);

	// Ressourcen freigeben
	for (i = 0; i < data->num_philos; i++)
		pthread_mutex_destroy(&data->forks[i]);

	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death_lock);

	// Speicher freigeben (falls du malloc verwendet hast)
	free(data->forks);
	free(data->philos);
	free(data);

	return (0);
}

