#include "philo.h"

void	ft_monitoring(void *monitor_void)
{
	t_monitor	monitor;
	struct timeval current_time;
	long time_diff;
	int		i;

	i = 0;
	monitor = (t_monitor *)monitor_void;
	while (1)
	{
		gettimeofday(current_time, NULL);
		while (i < monitor.args->n_philos)
		{
			time_diff = (current_time.tv_sec - monitor.philos[i]->last_meal_time.tv_sec) * 1000;
			time_diff += (current_time.tv_usec - monitor->philos[i]->last_meal_time.tv_usec) / 1000;
			if (time_diff > monitor.args->time_to_die)
			{
				pthread_mutex_lock(&monitor->args->monitor_lock);
				monitor->args->stop_simulating = 1;
				pthread_mutex_unlock(&monitor->args->monitor_lock);
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}
