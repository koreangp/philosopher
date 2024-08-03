/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:00:47 by pscala            #+#    #+#             */
/*   Updated: 2024/08/03 18:31:05 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_good_int(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	j = ft_strlen(&str[i]);
	if (j < 0)
		return (1);
	if (j == 10)
		return (ft_strncmp(str, "2147483647", j));
	else if (j > 10)
		return (1);
	return (0);
}

int	ft_pars(char **av)
{
	int	i;

	i = 1;
	if (!av[i])
		return (-1);
	while (av[i])
	{
		if (is_alnum(av[i]) == -1)
			return (-1);
		else if (is_good_int(av[i]) > 0)
			return (-1);
		i++;
	}
	return (0);
}

int	init_args(t_args *args, char **av, int ac)
{
	args->nb_of_philo = ft_atoi(av[1]);
	if (args->nb_of_philo == 0)
		return (-1);
	args->time_to_die = (ft_atoi(av[2]));
	args->dead = 0;
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->nb_of_time_to_eat = -1;
	args->flag = -1;
	args->philo_in_queue = 0;
	if (pthread_mutex_init(&args->printmutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&args->deadmutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&args->mutex_philo_in_queue, NULL) != 0)
		return (-1);
	if (ac == 6)
	{
		args->nb_of_time_to_eat = ft_atoi(av[5]);
		if (args->nb_of_time_to_eat == 0)
			return (-1);
	}
	args->start = -1;
	return (0);
}

int	init_tab_philos(t_philo **philos, t_args *args)
{
	int	i;

	i = 0;
	(*philos) = malloc(sizeof(t_philo) * args->nb_of_philo);
	if (!philos)
		return (printf("Erreur malloc struct"), -1);
	while (i < args->nb_of_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].last_meal = args->start;
		(*philos)[i].nb_of_meals = 0;
		(*philos)[i].args = args;
		(*philos)[i].nextfork = NULL;
		if (pthread_mutex_init((&(*philos)[i].fork), NULL) != 0)
			return (printf("Mutex error"), -1);
		if (pthread_mutex_init((&(*philos)[i].mealsmutex), NULL) != 0)
			return (printf("Mutex error"), -1);
		if (i + 1 == args->nb_of_philo && args->nb_of_philo != 1)
			(*philos)[i].nextfork = &(*philos)[0].fork;
		else if (args->nb_of_philo > 1)
			(*philos)[i].nextfork = &(*philos)[i + 1].fork;
		i++;
	}
	return (0);
}

// void	ft_print_args(t_args args)
// {
// 	printf("nombre de philo : %d\n", args.nb_of_philo);
// 	printf("temps pour mourir: %d\n", args.time_to_die);
// 	printf("temps pour manger: %d\n", args.time_to_eat);
// 	printf("temps pour zzzzz : %d\n", args.time_to_sleep);
// 	printf("nb de fois qu'il faut manger : %d\n", args.nb_of_time_to_eat);
// }

// void	ft_print_philos(t_philo **philos, t_args *args)
// {
// 	int	i;

// 	i = 0;
// 	while (i < args->nb_of_philo)
// 	{
// 		printf("id : %d\n", (*philos)[i].id);
// 		printf("last meal : %ld\n", (*philos)[i].last_meal);
// 		printf("nb of meal : %d\n", (*philos)[i].nb_of_meals);
// 		ft_print_args(*(*philos)[i].args);
// 		i++;
// 	}
// }