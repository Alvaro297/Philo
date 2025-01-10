#include "philo.h"

static int	ft_atoi(char *nbr)
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

static int	isnumber(char *nbr)
{
	int		i;

	i = 0;
	while (nbr[i])
	{
		if (!(nbr[i] >= 48 && nbr[i] <= 57))
			return (1);
		i++;
	}
	return (0);
}

int		ft_check_args(int argc, char **argv)
{
	int		i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (1);
	while (i < argc)
	{
		if (!is_number(argc[i]))
			return (1);
		i++;
	}
	return (0);
}
static void		ft_start_philo_help(t_philo *philo, t_args *args)
{
	int		i;

	i = 0;
	while (i < argc)
	{
		if (pthread_mutex_init(&args.forks[i], NULL) != 0)
		{
			perror("Failed to initialize mutex");
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&args.print_lock, NULL) != 0)
	{
		perror("Failed to initialize print_lock mutex");
		return (1);
	}
}

void		ft_start_philo(char **argv, int argc, t_philo *philo)
{
	t_args	args;
	int		i;

	i = 0;
	args.forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	args.n_philos = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args.number_eat = ft_atoi(argv[5]);
	else
		args.number_eat = -1;
	ft_start_philo_help(philo, &args);
	while (i < args.n_philos)
	{
		philo[i].id = i;
		philo[i].args = &args;
		philo[i].n_times_eat = 0;
		philo[i].last_meal_time = 0;
		philo[i].is_fork = 0;
	}
};
