#include "philo.h"

int	ft_atoi(char *nbr)
{
	int		result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		result = result * 10 + (nbr[i] - '0');
		i++;
	}
	return (result * sign);
}

static void	ft_start_philo_help(t_args *args, char **argv, int argc)
{
	int		i;

	i = 0;
	args->n_philos = ft_atoi(argv[1]);
	args->stop_simulating = 0;
	args->forks = malloc(sizeof(pthread_mutex_t) * args->n_philos);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->number_eat = ft_atoi(argv[5]);
	else
		args->number_eat = -1;
	while (i < args->n_philos)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			perror("Failed to initialize mutex");
		i++;
	}
	if (pthread_mutex_init(&args->monitor_lock, NULL) != 0)
		perror("Failed to initialize monitor_lock mutex");
	if (pthread_mutex_init(&args->print_lock, NULL) != 0)
		perror("Failed to initialize print_lock mutex");
}

t_philo		*ft_start_philo(char **argv, int argc)
{
	t_philo	*philo;
	t_args	*args;
	int		i;

	i = 0;
	args = malloc(sizeof(t_args));
	ft_start_philo_help(args, argv, argc);
	philo = malloc(sizeof(t_philo) * args->n_philos);
	 while (i < args->n_philos) {
		philo[i].id = i + 1;
		philo[i].n_times_eat = 0;
		gettimeofday(&philo[i].last_meal_time, NULL);
		philo[i].right_fork = i;
		if (args->n_philos == 1)
			philo[i].left_fork = -1;
		else if (i == 0)
			philo[i].left_fork = args->n_philos - 1;
		else
			philo[i].left_fork = i - 1;
		if (pthread_mutex_init(&philo[i].last_meal_time_mutex, NULL) != 0)
			perror("Failed to initialize mutex");
		philo[i].args = args;
		i++;
	}
	return (philo);
};

void	ft_free_all(t_philo *philo, t_monitor *monitor)
{
	int		i;

	i = 0;
	while (i < philo->args->n_philos)
		pthread_join(philo[i++].thread, NULL);
	pthread_join(monitor->monitor, NULL);
	i = 0;
	while (i < philo->args->n_philos)
	{
		pthread_mutex_destroy(&philo->args->forks[i]);
		pthread_mutex_destroy(&philo[i].last_meal_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&philo->args->monitor_lock);
	pthread_mutex_destroy(&philo->args->print_lock);
	free(philo->args->forks);
	free(philo->args);
	free(philo);
}
