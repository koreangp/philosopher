/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:04:59 by pscala            #+#    #+#             */
/*   Updated: 2024/08/03 16:12:01 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_sleep(long int time_usleep)
{
	long int	time;

	time = get_time();
	while (get_time() - time < time_usleep)
		usleep(500);
}

int	eating(t_philo *philo)
{
	if (is_he_dead(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->mealsmutex);
	philo->last_meal = get_time();
	philo->nb_of_meals++;
	pthread_mutex_unlock(&philo->mealsmutex);
	ft_print(philo, "is eating 🍝\n", YELLOW);
	ft_sleep(philo->args->time_to_eat);
	return (0);
}

int	sleep_and_think(t_philo *philo)
{
	if (is_he_dead(philo) == -1)
		return (-1);
	ft_print(philo, "is sleeping 😴\n", CYAN);
	ft_sleep(philo->args->time_to_sleep);
	if (is_he_dead(philo) == -1)
		return (-1);
	ft_print(philo, "is thinking 🤔💭\n", ORANGE);
	return (0);
}

int	grab_and_eat(t_philo *philo)
{
	if (philo->nextfork == NULL)
		return (case_one_philo(philo));
	if (philo_pos(philo) == -1)
		return (-1);
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

void	*routine(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	ft_wait_everyone(philo);
	if (philo->id % 2 == 0)
		usleep(800);
	while (1)
	{
		if (grab_and_eat(philo) == -1)
			break ;
		if (philo->nb_of_meals == philo->args->nb_of_time_to_eat)
			break ;
		if (sleep_and_think(philo) == -1)
			break ;
	}
	return (NULL);
}
