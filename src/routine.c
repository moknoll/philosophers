/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:01:04 by mknoll            #+#    #+#             */
/*   Updated: 2025/06/04 13:25:33 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long timestamp(t_data *data)
{
    return (get_time_in_ms() - data->start_time);
}


static void think(t_philo *philo)
{
	if(check_death(philo))
		return ;
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d is thinking\n", timestamp(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	usleep(500);
}

static int pick_up_forks(t_philo *philo)
{
    if (check_death(philo))
        return (1);

    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        if (check_death(philo))
        {
            pthread_mutex_unlock(philo->left_fork);
            return (1);
        }
        pthread_mutex_lock(&philo->data->print);
        printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
        pthread_mutex_unlock(&philo->data->print);

        pthread_mutex_lock(philo->right_fork);
        if (check_death(philo))
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            return (1);
        }
        pthread_mutex_lock(&philo->data->print);
        printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
        pthread_mutex_unlock(&philo->data->print);
    }
    else
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
    }
    return (0);
}


static void put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void eat(t_philo *philo)
{
    if (check_death(philo))
        return ;

    long long now = get_time_in_ms();

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




static void sleep_philo(t_philo *philo)
{
	if(check_death(philo))
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
	if(philo->id % 2 == 0)
		usleep(1000);
	// Warte, bis der globale Startzeitpunkt erreicht ist
	while (get_time_in_ms() < philo->data->start_time)
		usleep(100);
	

	// Setze den Zeitstempel des letzten Essens genau jetzt
	pthread_mutex_lock(&philo->data->death_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->data->death_lock);

	while (1)
	{
		if (check_death(philo))
			break;
		think(philo);
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
	}
	return (NULL);
}
