#include "philo.h"

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->args->print_lock);
	printf("Philosopher %d is thinking\n", philo->id);
	pthread_mutex_unlock(&args->print_lock);
	usleep(1000);
}

void	eating(t_philo	*philo)
{

}

void	sleeping(t_philo *philo)
{

}