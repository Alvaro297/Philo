#include "philo.h"

static void	*routine(void *philo_void)
{
	t_philo		*philo;

	philo = (t_philo *)philo_void;
	if (philo->id % 2 == 0)
		usleep(5000);
	while (1)
	{
		pthread_mutex_lock(&philo->args->monitor_lock);
		if (philo->args->stop_simulating)
		{
			pthread_mutex_unlock(&philo->args->monitor_lock);
			break;
		}
		pthread_mutex_unlock(&philo->args->monitor_lock);
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}

static void	philo(int argc, char **argv)
{
	t_philo		*philo;
	t_monitor	monitor;
	int			i;
	
	i = 0;
	philo = ft_start_philo(argv, argc);
	monitor.args = philo->args;
	monitor.philos = philo;
	if (pthread_create(&monitor.monitor, NULL, ft_monitoring, &monitor))
	{
		perror("Fallo en la creacion");
		return ;
	}
	while (i < philo->args->n_philos)
	{
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
	ft_free_all(philo, &monitor);
}

int	main(int argc, char **argv)
{
	if (ft_check_args(argc, argv))
	{
		printf("Error en los argumentos\n");
		return (EXIT_SUCCESS);
	}
	philo(argc, argv);
	return (EXIT_SUCCESS);
}
