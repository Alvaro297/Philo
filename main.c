#include "philo.h"

void	routine(void *philo_void)
{
	t_philo		philo;

	philo = (t_philo *) philo_void;
}

static void	philo(int argc, char **argv)
{
	t_philo	*philo;
	int		i;
	
	i = 0;
	philo = ft_start_philo(argv, argc, philo);
	while (i < philo->args->n_philos)
	{
		pthread_create(&philo[i].thread, NULL, routine, (void *) philo[i]);
		i++;
	}
	
}

int	main(int argc, char **argv)
{
	if (ft_check_args(argc, argv))
	{
		printf("Error en los argumentos\n")
		return (0);
	}
	philo(argc, argv);
	return (0);
}
