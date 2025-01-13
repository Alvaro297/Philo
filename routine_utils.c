#include "philo.h"

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_lock);
	printf("Philosopher %d is thinking\n", philo->id);
	pthread_mutex_unlock(&philo->args->print_lock);
	usleep(philo->args->time_to_sleep * 1000);
}

void	eating(t_philo	*philo)
{
	if (philo->left_fork == -1)
		usleep(philo->args->time_to_die * 1000 + 1);
	else
	{
		pthread_mutex_lock(&philo->args->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->args->monitor_lock);
		if (philo->n_times_eat >= philo->args->number_eat)
		{
			pthread_mutex_unlock(&philo->args->monitor_lock);
			pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
			return;
		}
		pthread_mutex_unlock(&philo->args->monitor_lock);
		pthread_mutex_lock(&philo->args->print_lock);
		printf("Philosopher %d is eating\n", philo->id);
		pthread_mutex_unlock(&philo->args->print_lock);
		gettimeofday(&philo->last_meal_time, NULL);
		usleep(philo->args->time_to_eat * 1000);
		philo->n_times_eat++;
		pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
	}
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_lock);
	printf("Philosopher %d is sleeping\n", philo->id);
	pthread_mutex_unlock(&philo->args->print_lock);
	usleep(philo->args->time_to_sleep);
}
