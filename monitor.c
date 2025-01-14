#include "philo.h"

static int	ft_all_eating(t_monitor *monitor)
{
	int		i;

	i = 0;
	while (i < monitor->args->n_philos)
	{
		if (monitor->args->number_eat == -1 || monitor->philos[i].n_times_eat < monitor->args->number_eat)
			return (0);
		i++;
	}
	pthread_mutex_lock(&monitor->args->monitor_lock);
	monitor->args->stop_simulating = 1;
	pthread_mutex_unlock(&monitor->args->monitor_lock);
	return (1);
}

static int	ft_die_philo(t_monitor *monitor, t_philo *philo, struct timeval current_time)
{
	long time_diff;

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
		printf(RED "Philosopher %d has died\n" RESET, philo->id);
		pthread_mutex_unlock(&monitor->args->print_lock);
		return (1);
	}
	return (0);
}

void	*ft_monitoring(void *monitor_void)
{
	t_monitor	*monitor;
	struct timeval current_time;
	int		i;

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
