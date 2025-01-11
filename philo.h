#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_args
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_eat;
	pthread_mutex_t	*forks;
	int				stop_simulating;
	pthread_mutex_t	monitor_lock;
	pthread_mutex_t	print_lock;
}	t_args;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	int					n_times_eat;
	struct timeval		last_meal_time;
	int					right_fork;
	int					left_fork;
	t_args				*args;
}	t_philo;

typedef struct s_monitor
{
	pthread_t	monitor;
	t_args		*args;
	t_philo		**philos;
}	t_monitor;


t_philo	*ft_start_philo(char **argv, int argc);
int		ft_check_args(int argc, int argc, char **argv);
void	ft_monitoring(void *monitor_void);
void	thinking(t_philo *philo);
void	eating(t_philo	*philo);
void	sleeping(t_philo *philo);
#endif
