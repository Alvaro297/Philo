#include "philo.h"

void	routine(void *philo_void)
{
	t_philo		*philo;

	philo = (t_philo *)philo_void;

	if (philo->id % 2 == 0)
		usleep(5000);
	while (1)
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
}

static void	philo(int argc, char **argv)
{
	t_philo		*philo;
	t_monitor	monitor;
	int			i;
	
	i = 0;
	philo = ft_start_philo(argv, argc, philo);
	monitor.args = philo->args;
	monitor.philos = &philo;
	if (pthread_create(&monitor.monitor, NULL, ft_monitoring, (void *)&monitor);)
	{
		perror("Fallo en la creacion");
		return (EXIT_FAILURE);
	}
	while (i < philo->args->n_philos)
	{
		pthread_create(&philo[i].thread, NULL, routine, (void *)&philo[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (ft_check_args(argc, argv))
	{
		printf("Error en los argumentos\n")
		return (EXIT_SUCCESS);
	}
	philo(argc, argv);
	return (EXIT_SUCCESS);
}
