/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:20:53 by pscala            #+#    #+#             */
/*   Updated: 2024/07/14 18:44:34 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_alnum(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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

	i = 0;
	if (!av[i])
		return (0);
	while (av[i])
	{
		if (!is_alnum(av[i]))
			return (0);
		else if (is_good_int(av[i]) > 0)
			return (0);
		i++;
	}
	return (1);
}

long int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("could not get time"), -1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	init_args(t_args *args, char **av, int ac)
{
	args->nb_of_philo = ft_atoi(av[1]);
	if (args->nb_of_philo == 0)
		return (-1);
	args->time_to_die = (ft_atoi(av[2]) / 1000);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->nb_of_time_to_eat = -1;
	if (pthread_mutex_init(&args->printmutex, NULL) != 0)
		return (-1);
	if (ac == 6)
		args->nb_of_time_to_eat = ft_atoi(av[5]);
	args->start = get_time();
	if (args->start == -1)
		return (-1);
	return (0);
}

void	ft_print_args(t_args args)
{
	printf("nombre de philo : %d\n", args.nb_of_philo);
	printf("temps pour mourir: %d\n", args.time_to_die);
	printf("temps pour manger: %d\n", args.time_to_eat);
	printf("temps pour zzzzz : %d\n", args.time_to_sleep);
	printf("nb de fois qu'il faut manger : %d\n", args.nb_of_time_to_eat);
}

void	ft_print_philos(t_philo **philos, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_of_philo)
	{
		printf("id : %d\n", (*philos)[i].id);
		printf("last meal : %ld\n", (*philos)[i].last_meal);
		printf("nb of meal : %d\n", (*philos)[i].nb_of_meals);
		ft_print_args(*(*philos)[i].args);
		i++;
	}
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

int	check_if_dead(t_philo *philo, long int time)
{
	long int	real_time;

	real_time = get_time();
	if (real_time - philo->last_meal > philo->args->time_to_die)
	{
		pthread_mutex_lock(&philo->args->printmutex);
		printf("%s[%ld] %d  died 💀 *rip*%s\n\n", RED, time, philo->id, RESET);
		pthread_mutex_unlock(&philo->args->printmutex);
		return (-1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	long int	time;

	time = get_time() - philo->args->start;
	if (check_if_dead(philo, time) == -1)
		return (-1);
	pthread_mutex_lock(&philo->mealsmutex);
	pthread_mutex_lock(&philo->args->printmutex);
	printf("%s[%ld] %d  is eating 🍝 *yummy*%s\n\n", YELLOW, time, philo->id,
		RESET);
	pthread_mutex_unlock(&philo->args->printmutex);
	philo->last_meal = get_time();
	usleep(philo->args->time_to_eat);
	philo->nb_of_meals++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mealsmutex);
	return (0);
}

int	grab_and_eat(t_philo *philo)
{
	long int	time;

	time = get_time() - philo->args->start;
	if (philo->nextfork == NULL)
		return (printf("only 1 fork\n"), -1);
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(philo->nextfork);
	pthread_mutex_lock(&philo->args->printmutex);
	printf("%s[%ld] %d  has taken a fork%s 🍴\n\n", PURPLE, time, philo->id,
		RESET);
	pthread_mutex_unlock(&philo->args->printmutex);
	time = get_time() - philo->args->start;
	pthread_mutex_lock(&philo->args->printmutex);
	printf("%s[%ld] %d  has taken a fork%s 🍴\n\n", PURPLE, time, philo->id,
		RESET);
	pthread_mutex_unlock(&philo->args->printmutex);
	if (eating(philo) == -1)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->nextfork);
		return (-1);
	}
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->nextfork);
	return (0);
}

void	sleep_and_think(t_philo *philo)
{
	long int	time;

	time = get_time() - philo->args->start;
	pthread_mutex_lock(&philo->args->printmutex);
	printf("%s[%ld] %d  is sleeping 🛏️  *zzz*%s\n\n", CYAN, time, philo->id,
		RESET);
	pthread_mutex_unlock(&philo->args->printmutex);
	usleep(philo->args->time_to_sleep);
	pthread_mutex_lock(&philo->args->printmutex);
	printf("%s[%ld] %d  is thinking 🤔💭 *hmmm*%s\n\n", ORANGE, time, philo->id,
		RESET);
	pthread_mutex_unlock(&philo->args->printmutex);
}

void	*routine(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	while (1)
	{
		if (philo->nb_of_meals == philo->args->nb_of_time_to_eat)
			break ;
		if (grab_and_eat(philo) == -1)
			break ;
		sleep_and_think(philo);
	}
	return (NULL);
}

int	creat_threads(t_philo *philos, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_of_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < args->nb_of_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
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
			return (printf("Pars error\n"), 1);
		if (init_args(&args, av, ac) == -1)
			return (printf("bad arguments\n"), 1);
		if (init_tab_philos(&philos, &args) == -1)
			return (1);
		// ft_print_philos(&philos, &args);
		if (creat_threads(philos, &args) == -1)
			return (1);
		// free_mutex();
	}
	else
		return (printf("bad number of arguments\n"), 1);
	return (0);
}
