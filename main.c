#include "philo.h"

static void	philo(int argc, char **argv)
{
	t_philo	*philo;
	
	philo = malloc(sizeof(philo) * argv[1]);
	ft_start_philo(argv, argc, philo);
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
