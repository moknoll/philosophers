/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:03:40 by mknoll            #+#    #+#             */
/*   Updated: 2025/06/05 14:05:11 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	pick_up_fork_even(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	pthread_mutex_lock(philo->left_fork);
	if (check_death(philo))
		return (pthread_mutex_unlock(philo->left_fork), 1);
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(philo->right_fork);
	if (check_death(philo))
		return (pthread_mutex_unlock(philo->right_fork),
			pthread_mutex_unlock(philo->left_fork), 1);
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

int	pick_up_fork_uneven(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(philo->left_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
