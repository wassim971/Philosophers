/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wassim <wassim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 02:45:21 by wassim            #+#    #+#             */
/*   Updated: 2025/05/28 02:45:23 by wassim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/philo.h"

void	protect_write(t_philo *philo, char *str)
{
	if (protect_check(philo))
	{
		pthread_mutex_lock(philo->shared->write_protect);
		printf(str, get_timestamp(philo->tmstp), philo->index);
		pthread_mutex_unlock(philo->shared->write_protect);
	}
}

int	protect_check(t_philo *philo)
{
	int		value;

	value = 1;
	pthread_mutex_lock(philo->shared->dead);
	if (*(philo->shared->is_dead) == 1)
		value = 0;
	pthread_mutex_unlock(philo->shared->dead);
	return (value);
}

void	lock(t_philo *philo)
{
	if (philo->index % 2 != 0)
	{
		pthread_mutex_lock(&(philo->fork));
		protect_write(philo, "%d Philos %d as taken a fork\n");
		if (philo->next->balise != 1)
			pthread_mutex_lock(&(philo->next->fork));
		else
			pthread_mutex_lock(&(philo->next->next->fork));
		protect_write(philo, "%d Philos %d as taken a fork\n");
	}
	else
	{
		if (philo->next->balise != 1)
			pthread_mutex_lock(&(philo->next->fork));
		else
			pthread_mutex_lock(&(philo->next->next->fork));
		protect_write(philo, "%d Philos %d as taken a fork\n");
		pthread_mutex_lock(&(philo->fork));
		protect_write(philo, "%d Philos %d as taken a fork\n");
	}
}

void	unlock(t_philo *philo)
{
	if (philo->index % 2 == 0 && philo->next->balise != 1)
	{
		pthread_mutex_unlock(&(philo->fork));
		usleep(100);
		pthread_mutex_unlock(&(philo->next->fork));
	}
	else if (philo->index % 2 != 0 && philo->next->balise != 1)
	{
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(&(philo->next->fork));
	}
	else if (philo->next->balise == 1 && philo->index % 2 != 0)
	{
		pthread_mutex_unlock(&(philo->next->next->fork));
		pthread_mutex_unlock(&(philo->fork));
	}
	else if (philo->next->balise == 1 && philo->index % 2 == 0)
	{
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(&(philo->next->next->fork));
	}
}
