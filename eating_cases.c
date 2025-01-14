#include "philo.h"

void	eating_case1(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->args->monitor_lock);
	if (philo->args->stop_simulating)
	{
		pthread_mutex_unlock(&philo->args->monitor_lock);
		pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
		return ;
	}
	pthread_mutex_unlock(&philo->args->monitor_lock);
	pthread_mutex_lock(&philo->args->print_lock);
	printf(YELLOW "Philosopher %d has taken a fork\n" RESET, philo->id);
	pthread_mutex_unlock(&philo->args->print_lock);
	pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->args->monitor_lock);
	if (philo->args->stop_simulating)
	{
		pthread_mutex_unlock(&philo->args->monitor_lock);
		pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
		return ;
	}
	pthread_mutex_unlock(&philo->args->monitor_lock);
	pthread_mutex_lock(&philo->args->print_lock);
	printf(YELLOW "Philosopher %d has taken a fork\n" RESET, philo->id);
	pthread_mutex_unlock(&philo->args->print_lock);
}

void	eating_case2(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->args->monitor_lock);
	if (philo->args->stop_simulating)
	{
		pthread_mutex_unlock(&philo->args->monitor_lock);
		pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
		return;
	}
	pthread_mutex_unlock(&philo->args->monitor_lock);
	pthread_mutex_lock(&philo->args->print_lock);
	printf(YELLOW "Philosopher %d has taken a fork\n" RESET, philo->id);
	pthread_mutex_unlock(&philo->args->print_lock);
	pthread_mutex_lock(&philo->args->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->args->monitor_lock);
	if (philo->args->stop_simulating)
	{
		pthread_mutex_unlock(&philo->args->monitor_lock);
		pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
		return;
	}
	pthread_mutex_unlock(&philo->args->monitor_lock);
	pthread_mutex_lock(&philo->args->print_lock);
	printf(YELLOW "Philosopher %d has taken a fork\n" RESET, philo->id);
	pthread_mutex_unlock(&philo->args->print_lock);
}
