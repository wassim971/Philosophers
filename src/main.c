/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wassim <wassim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 02:45:50 by wassim            #+#    #+#             */
/*   Updated: 2025/05/28 02:46:28 by wassim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char const *argv[])
{
	t_arg		arg;

	if (argc == 5)
		arg.need_eat = -1;
	else if (argc >= 6)
		arg.need_eat = ft_atoi((char *)argv[5]);
	if (argc >= 5)
	{
		arg.nb_philo = ft_atoi((char *)argv[1]);
		arg.t_dead = ft_atoi((char *)argv[2]);
		arg.t_eat = ft_atoi((char *)argv[3]);
		arg.t_sleep = ft_atoi((char *)argv[4]);
		if (check_main(argc, (char **)argv))
			philosopher(arg);
		else
			ft_error("Error\n");
	}
	return (0);
}
