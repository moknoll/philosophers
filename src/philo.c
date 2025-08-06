/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritz <moritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:00:59 by mknoll            #+#    #+#             */
/*   Updated: 2025/08/04 08:43:10 by moritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// void	create_threads(t_philo *philos)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philos[0].data->num_philos)
// 	{
// 		if (pthread_create(&philos[i].thread,
// 				NULL, philo_routine, (void *)&philos[i]))
// 		{
// 			// printf("Failed to create thread for philospher %d\n", philos[i]);
// 			return ;
// 		}
// 	}
// }
