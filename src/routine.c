/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:01:04 by mknoll            #+#    #+#             */
/*   Updated: 2025/06/05 14:29:46 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


static void	think(t_philo *philo)
{
	if (check_death(philo))
		return ;
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d is thinking\n", timestamp(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	usleep(500);
}

static void	eat(t_philo *philo)
{
	long long	now;

	if (check_death(philo))
		return ;
	now = get_time_in_ms();
	pthread_mutex_lock(&philo->data->death_lock);
	philo->last_meal = now;
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d is eating\n", timestamp(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	smart_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->meals++;
	pthread_mutex_unlock(&philo->data->meal_lock);
}

static void	sleep_philo(t_philo *philo)
{
	if (check_death(philo))
		return ;
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d is sleeping\n", timestamp(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	smart_usleep(philo, philo->data->time_to_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (get_time_in_ms() < philo->data->start_time)
		usleep(100);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->data->meal_lock);
	while (1)
	{
		if (check_death(philo))
			break ;
		think(philo);
		if (philo->id % 2 == 0)
			pick_up_fork_even(philo);
		else
			pick_up_fork_uneven(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
	}
	return (NULL);
}
