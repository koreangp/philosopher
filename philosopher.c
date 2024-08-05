/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:20:53 by pscala            #+#    #+#             */
/*   Updated: 2024/08/05 13:59:45 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("could not get time"), -1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	creat_threads(t_philo *philos, t_args *args)
{
	int			i;
	pthread_t	supervisor;

	i = 0;
	while (i < args->nb_of_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_create(&supervisor, NULL, &visor_routine, philos) != 0)
		return (-1);
	i = 0;
	while (i < args->nb_of_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(supervisor, NULL) != 0)
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	*philos;

	philos = NULL;
	if (ac == 5 || ac == 6)
	{
		if (ft_pars(av) == -1)
			return (printf(RED "ERROR: parsing\n" RESET), 1);
		if (init_args(&args, av, ac) == -1)
			return (printf(RED "ERROR: couldnt init\n" RESET), 1);
		if (init_tab_philos(&philos, &args) == -1)
			return (printf(RED "ERROR: couldnt init\n" RESET), 1);
		if (creat_threads(philos, &args) == -1)
			return (printf(RED "ERROR: threads\n" RESET), 1);
	}
	else
		return (printf(RED "ERROR: %d arguments\n" RESET, ac), 1);
	free(philos);
	return (0);
}
