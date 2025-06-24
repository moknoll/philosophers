/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:57:30 by mknoll            #+#    #+#             */
/*   Updated: 2025/06/24 14:38:00 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_up(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->meal_lock);
	free(data->forks);
	free(data->philos);
	free(data);
}

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
	data->death = 0;
	return (data);
}

int	start_threads(pthread_t *monitor_thread, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread,
				NULL, philo_routine, &data->philos[i]) != 0)
		{
			printf("Error creating philosopher thread %d\n", i + 1);
			return (0);
		}
		i++;
	}
	if (pthread_create(monitor_thread, NULL, monitor, data) != 0)
	{
		printf("Error creating monitor thread\n");
		return (0);
	}
	return (1);
}

int	handle_one(t_data *data)
{
	printf("%lld %d has taken a fork\n", timestamp(data), 1);
	usleep(data->time_to_die * 1000);
	printf("%lld %d died\n", timestamp(data), 1);
	free(data);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	pthread_t	monitor_thread;
	int			i;

	if (!check_args(argc, argv))
		return (1);
	data = get_data(argv);
	if (!data)
		return (1);
	data->start_time = get_time_in_ms();
	if (data->num_philos == 1)
		return (handle_one(data));
	init_philo_and_forks(data);
	if (!start_threads(&monitor_thread, data))
	{
		clean_up(data);
		return (1);
	}
	i = 0;
	while (i < data->num_philos)
		pthread_join(data->philos[i++].thread, NULL);
	pthread_join(monitor_thread, NULL);
	clean_up(data);
	return (0);
}
