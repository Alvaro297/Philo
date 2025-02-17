/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-16 12:42:45 by alvamart          #+#    #+#             */
/*   Updated: 2025-01-16 12:42:45 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_all_eating(t_monitor *monitor)
{
	int		i;

	i = 0;
	while (i < monitor->args->n_philos)
	{
		pthread_mutex_lock(&monitor->philos[i].last_meal_time_mutex);
		if (monitor->args->number_eat == -1
			|| monitor->philos[i].n_times_eat < monitor->args->number_eat)
		{
			pthread_mutex_unlock(&monitor->philos[i].last_meal_time_mutex);
			return (0);
		}
		pthread_mutex_unlock(&monitor->philos[i].last_meal_time_mutex);
		i++;
	}
	pthread_mutex_lock(&monitor->args->monitor_lock);
	monitor->args->stop_simulating = 1;
	pthread_mutex_unlock(&monitor->args->monitor_lock);
	return (1);
}

static int	ft_die_philo(t_monitor *monitor, t_philo *philo,
	struct timeval current_time)
{
	long	time_diff;
	long	milisec;

	pthread_mutex_lock(&philo->last_meal_time_mutex);
	time_diff = (current_time.tv_sec - philo->last_meal_time.tv_sec) * 1000;
	time_diff += (current_time.tv_usec - philo->last_meal_time.tv_usec) / 1000;
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	if (time_diff > monitor->args->time_to_die)
	{
		pthread_mutex_lock(&monitor->args->monitor_lock);
		monitor->args->stop_simulating = 1;
		pthread_mutex_unlock(&monitor->args->monitor_lock);
		pthread_mutex_lock(&monitor->args->print_lock);
		milisec = get_milliseconds();
		printf(RED "timestamp_in_ms %ld Philosopher %d has died\n" RESET,
			milisec, philo->id);
		pthread_mutex_unlock(&monitor->args->print_lock);
		return (1);
	}
	return (0);
}

void	*ft_monitoring(void *monitor_void)
{
	t_monitor		*monitor;
	struct timeval	current_time;
	int				i;

	monitor = (t_monitor *)monitor_void;
	while (1)
	{
		i = 0;
		gettimeofday(&current_time, NULL);
		while (i < monitor->args->n_philos)
		{
			if (ft_die_philo(monitor, &monitor->philos[i], current_time) == 1)
				return (NULL);
			i++;
		}
		if (ft_all_eating(monitor) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
