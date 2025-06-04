/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:02:32 by mknoll            #+#    #+#             */
/*   Updated: 2025/06/04 13:12:26 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

long long get_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
}


void smart_usleep(t_philo *philo, long time_ms)
{
    long start = get_time_in_ms();
    while ((get_time_in_ms() - start) < time_ms)
    {
        if (check_death(philo))
            break;
        usleep(1000);  // 1 ms
    }
}

int check_death(t_philo *philo)
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
