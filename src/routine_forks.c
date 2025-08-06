/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritz <moritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:03:40 by mknoll            #+#    #+#             */
/*   Updated: 2025/08/04 06:29:35 by moritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork_flag_lock);
    philo->has_l_fork = false;
    philo->has_r_fork = false;
    pthread_mutex_unlock(&philo->fork_flag_lock);
}

int	pick_up_fork_even(t_philo *philo)
{
    init_forks(philo);
    if (check_death(philo))
        return (1);
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(&philo->fork_flag_lock);
    philo->has_l_fork = true;
    pthread_mutex_unlock(&philo->fork_flag_lock);
    if (check_death(philo))
        return (pthread_mutex_unlock(philo->left_fork),
            pthread_mutex_lock(&philo->fork_flag_lock), philo->has_l_fork = false, pthread_mutex_unlock(&philo->fork_flag_lock), 1);
    pthread_mutex_lock(&philo->data->print);
    printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
    pthread_mutex_unlock(&philo->data->print);
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(&philo->fork_flag_lock);
    philo->has_r_fork = true;
    pthread_mutex_unlock(&philo->fork_flag_lock);
    if (check_death(philo))
        return (pthread_mutex_unlock(philo->right_fork),
            pthread_mutex_unlock(philo->left_fork),
            pthread_mutex_lock(&philo->fork_flag_lock), philo->has_r_fork = false, philo->has_l_fork = false, pthread_mutex_unlock(&philo->fork_flag_lock), 1);
    pthread_mutex_lock(&philo->data->print);
    printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
    pthread_mutex_unlock(&philo->data->print);
    return (0);
}

int	pick_up_fork_uneven(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(&philo->fork_flag_lock);
    philo->has_r_fork = true;
    pthread_mutex_unlock(&philo->fork_flag_lock);
    if (check_death(philo))
        return (pthread_mutex_unlock(philo->right_fork),
            philo->has_r_fork = false, 1);
    pthread_mutex_lock(&philo->data->print);
    printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
    pthread_mutex_unlock(&philo->data->print);
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(&philo->fork_flag_lock);
    philo->has_l_fork = true;
    pthread_mutex_unlock(&philo->fork_flag_lock);
    if (check_death(philo))
        return (pthread_mutex_unlock(philo->left_fork),
            pthread_mutex_unlock(philo->right_fork),
            philo->has_l_fork = false, philo->has_r_fork = false, 1);
    pthread_mutex_lock(&philo->data->print);
    printf("%lld %d has taken a fork\n", timestamp(philo->data), philo->id);
    pthread_mutex_unlock(&philo->data->print);
    return (0);
}

void	put_down_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork_flag_lock);
    if (philo->has_r_fork)
    {
        philo->has_r_fork = false;
        pthread_mutex_unlock(philo->right_fork);
    }
    if (philo->has_l_fork)
    {
        philo->has_l_fork = false;
        pthread_mutex_unlock(philo->left_fork);
    }
    pthread_mutex_unlock(&philo->fork_flag_lock);
}
