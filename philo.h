#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_args
{
	int		n_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
} t_args;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	int			n_times_eat;
	long		last_meal_time;
	int			is_fork;
	t_args		*args;
} t_philo;

void	ft_start_philo(char **argv, t_philo *philo);
int		ft_check_args(int argc, int argc, char **argv);
#endif
