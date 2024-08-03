/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:13:04 by pscala            #+#    #+#             */
/*   Updated: 2024/08/03 18:30:02 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_wait_everyone(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_philo_in_queue);
	philo->args->philo_in_queue++;
	pthread_mutex_unlock(&philo->args->mutex_philo_in_queue);
	while (1)
	{
		pthread_mutex_lock(&philo->args->mutex_philo_in_queue);
		if (philo->args->philo_in_queue == philo->args->nb_of_philo)
		{
			if (philo->args->flag == -1)
			{
				philo->args->flag = 0;
				philo->args->start = get_time();
			}
			pthread_mutex_lock(&philo->mealsmutex);
			philo->last_meal = philo->args->start;
			pthread_mutex_unlock(&philo->mealsmutex);
			pthread_mutex_unlock(&philo->args->mutex_philo_in_queue);
			break ;
		}
		pthread_mutex_unlock(&philo->args->mutex_philo_in_queue);
		usleep(500);
	}
}

int	philo_pos(t_philo *philo)
{
	if (philo->id == philo->args->nb_of_philo)
	{
		pthread_mutex_lock(&philo->fork);
		if (is_he_dead(philo) == -1)
			return (pthread_mutex_unlock(&philo->fork), -1);
		ft_print(philo, "has taken a fork🍴\n", PURPLE);
		pthread_mutex_lock(philo->nextfork);
		if (is_he_dead(philo) == -1)
			return (pthread_mutex_unlock(&philo->fork),
				pthread_mutex_unlock(philo->nextfork), -1);
		ft_print(philo, "has taken a fork🍴\n", PURPLE);
	}
	else
	{
		pthread_mutex_lock(philo->nextfork);
		if (is_he_dead(philo) == -1)
			return (pthread_mutex_unlock(philo->nextfork), -1);
		ft_print(philo, "has taken a fork🍴\n", PURPLE);
		pthread_mutex_lock(&philo->fork);
		if (is_he_dead(philo) == -1)
			return (pthread_mutex_unlock(&philo->fork),
				pthread_mutex_unlock(philo->nextfork), -1);
		ft_print(philo, "has taken a fork🍴\n", PURPLE);
	}
	return (0);
}

int	case_one_philo(t_philo *philo)
{
	long int	time;

	time = get_time();
	ft_print(philo, "has taken a fork🍴\n", PURPLE);
	while (get_time() - time < philo->args->time_to_die)
		usleep(100);
	return (-1);
}

int	is_he_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->deadmutex);
	if (philo->args->dead == 1)
		return (pthread_mutex_unlock(&philo->args->deadmutex), -1);
	pthread_mutex_unlock(&philo->args->deadmutex);
	return (0);
}

void	ft_print(t_philo *philo, char *str, char *color)
{
	long int	time;

	time = get_time() - philo->args->start;
	pthread_mutex_lock(&philo->args->printmutex);
	printf("%s[%ld] %d %s" RESET, color, time, philo->id, str);
	pthread_mutex_unlock(&philo->args->printmutex);
}
