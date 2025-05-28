/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wassim <wassim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 02:45:28 by wassim            #+#    #+#             */
/*   Updated: 2025/05/28 02:45:32 by wassim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/philo.h"

static void	create_thread(t_philo *philo)
{
	t_philo		*buff;

	buff = philo;
	while (buff->balise != 1)
	{
		pthread_create(&(buff->thread), NULL, &routine, buff);
		usleep(philo->index * 100);
		buff = buff->next;
	}
}

static void	exit_thread(t_philo *philo)
{
	t_philo		*buff;

	buff = philo;
	while (buff->balise != 1)
	{
		if (!(buff->index == 1 && buff->next->balise == 1))
			pthread_join(buff->thread, NULL);
		buff = buff->next;
	}
	pthread_mutex_destroy(philo->shared->write_protect);
	pthread_mutex_destroy(philo->shared->dead);
	free(philo->shared->dead);
	free(philo->shared->write_protect);
	free(philo->shared->is_dead);
	free(philo->shared);
	while (philo->balise != 1)
	{
		buff = philo->next;
		pthread_mutex_destroy(&(philo->fork));
		pthread_mutex_destroy(&(philo->count_protect));
		free(philo);
		philo = buff;
	}
	free(philo);
}

void	philosopher(t_arg arg)
{
	t_philo			*philo;
	t_philo			*buff;
	t_shared		*shared;

	if (arg.nb_philo <= 0 || arg.t_dead <= 0
		|| arg.t_eat <= 0 || arg.t_sleep <= 0)
		return ;
	shared = set_shared(arg);
	philo = set_list(arg.nb_philo, shared);
	if (philo == NULL)
		return ;
	buff = philo;
	if (arg.nb_philo > 1)
		create_thread(buff);
	monitoring(buff);
	exit_thread(philo);
}
