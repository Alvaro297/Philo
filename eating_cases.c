/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-16 12:43:32 by alvamart          #+#    #+#             */
/*   Updated: 2025-01-16 12:43:32 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(t_philo *philo)
{
	long	milisec;

	pthread_mutex_lock(&philo->args->print_lock);
	milisec = get_milliseconds();
	printf(YELLOW "%ld Philosopher %d has taken a fork\n" RESET,
		milisec, philo->id);
	pthread_mutex_unlock(&philo->args->print_lock);
}

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
	take_fork(philo);
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
	take_fork(philo);
}

void	eating_case2(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->args->monitor_lock);
	if (philo->args->stop_simulating)
	{
		pthread_mutex_unlock(&philo->args->monitor_lock);
		pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
		return ;
	}
	pthread_mutex_unlock(&philo->args->monitor_lock);
	take_fork(philo);
	pthread_mutex_lock(&philo->args->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->args->monitor_lock);
	if (philo->args->stop_simulating)
	{
		pthread_mutex_unlock(&philo->args->monitor_lock);
		pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
		return ;
	}
	pthread_mutex_unlock(&philo->args->monitor_lock);
	take_fork(philo);
}
