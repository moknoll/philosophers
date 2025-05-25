/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:57:30 by mknoll            #+#    #+#             */
/*   Updated: 2025/05/25 16:32:45 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void	print_data(t_data *data)
{
	printf("Number of philosophers: %d\n", data->num_philos);
	printf("Time to die:            %d ms\n", data->time_to_die);
	printf("Time to eat:            %d ms\n", data->time_to_eat);
	printf("Time to sleep:          %d ms\n", data->time_to_sleep);
	printf("Current time: 			%ld ms\n", data->start_time);
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
	return (data);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 5)
	{
		printf("Error Usage: ./philo [number_of_philosopher] [time_to_die] [time_to_eat] [time_to_sleep]\n");
		return (1);
	}
	data = get_data(argv);
	if (!data)
		return (1);
	print_data(data);
	init_philos_and_forks(data);
	data->start_time = get_time_in_ms();
	create_threads(data->philos);
	free(data);
	return (0);
}
