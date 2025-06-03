/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:01:04 by mknoll            #+#    #+#             */
/*   Updated: 2025/06/03 12:09:19 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	timestamp(t_data *data)
{
	return (get_time_in_ms() - data->start_time);
}

static int check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_lock);
	if (philo->data->death)
	{
		pthread_mutex_unlock(&philo->data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	return (0);
}

static void think(t_philo *philo)
{
	if (check_death(philo))
		return;
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d is thinking\n", timestamp(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->print);
}
static void pick_up_forks(t_philo *philo)
{
	if (check_death(philo))
		return;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->data->print);
		printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print);

		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->data->print);
		printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->data->print);
		printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print);

		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->data->print);
		printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
}


static void put_down_forks(t_philo *philo)
{
	if (check_death(philo))
		return;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void eat(t_philo *philo)
{
	if (check_death(philo))
		return;

	pthread_mutex_lock(&philo->data->death_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->data->death_lock);

	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d is eating\n", timestamp(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	usleep(philo->data->time_to_eat * 1000);
	philo->meals++;
}



static void sleep_philo(t_philo *philo)
{
    if (check_death(philo))
        return;

    pthread_mutex_lock(&philo->data->print);
    printf("%lld %d is sleeping\n", timestamp(philo->data), philo->id);
    pthread_mutex_unlock(&philo->data->print);

    usleep(philo->data->time_to_sleep * 1000);
}


void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_death(philo))
			break;
		think(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
		usleep(1000);
	}
	return (NULL);
}
