/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-16 12:41:04 by alvamart          #+#    #+#             */
/*   Updated: 2025-01-16 12:41:04 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_forks(t_philo	*philo)
{
	if (philo->left_fork < philo->right_fork)
		eating_case1(philo);
	else
		eating_case2(philo);
}

static void	eating_help(t_philo	*philo)
{
	pthread_mutex_lock(&philo->args->print_lock);
	printf(GREEN "Philosopher %d is eating\n" RESET, philo->id);
	pthread_mutex_unlock(&philo->args->print_lock);
	pthread_mutex_lock(&philo->last_meal_time_mutex);
	gettimeofday(&philo->last_meal_time, NULL);
	philo->n_times_eat++;
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	usleep(philo->args->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
}

void	eating(t_philo *philo)
{
	if (philo->left_fork == -1)
		usleep(philo->args->time_to_die * 1000 + 1);
	else
	{
		print_forks(philo);
		pthread_mutex_lock(&philo->args->monitor_lock);
		if ((philo->n_times_eat >= philo->args->number_eat
				&& philo->args->number_eat != -1)
			|| philo->args->stop_simulating)
		{
			pthread_mutex_unlock(&philo->args->monitor_lock);
			return ;
		}
		pthread_mutex_unlock(&philo->args->monitor_lock);
		eating_help(philo);
	}
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->monitor_lock);
	if (philo->args->stop_simulating)
	{
		pthread_mutex_unlock(&philo->args->monitor_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->args->monitor_lock);
	pthread_mutex_lock(&philo->args->print_lock);
	printf(BLUE "Philosopher %d is sleeping\n" RESET, philo->id);
	pthread_mutex_unlock(&philo->args->print_lock);
	usleep(philo->args->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->monitor_lock);
	if (philo->args->stop_simulating)
	{
		pthread_mutex_unlock(&philo->args->monitor_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->args->monitor_lock);
	pthread_mutex_lock(&philo->args->print_lock);
	printf("Philosopher %d is thinking\n", philo->id);
	pthread_mutex_unlock(&philo->args->print_lock);
	usleep(1000);
}
