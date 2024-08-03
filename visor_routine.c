/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visor_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:14:57 by pscala            #+#    #+#             */
/*   Updated: 2024/08/03 18:32:36 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_if_dead(t_philo *philo)
{
	if (get_time() - philo->last_meal > philo->args->time_to_die)
	{
		pthread_mutex_lock(&philo->args->deadmutex);
		philo->args->dead = 1;
		pthread_mutex_unlock(&philo->args->deadmutex);
		return (ft_print(philo, "died 💀 *rip*\n", RED), -1);
	}
	return (0);
}

void	visor_loop(t_philo *philos, int i, int complete)
{
	while (i < philos->args->nb_of_philo
		&& complete < philos->args->nb_of_philo)
	{
		pthread_mutex_lock(&philos[i].mealsmutex);
		if (philos[i].nb_of_meals != philos->args->nb_of_time_to_eat
			&& check_if_dead(&philos[i]) == -1)
		{
			pthread_mutex_unlock(&philos[i].mealsmutex);
			break ;
		}
		else if (philos[i].nb_of_meals == philos->args->nb_of_time_to_eat)
			complete++;
		pthread_mutex_unlock(&philos[i].mealsmutex);
		if (i + 1 == philos->args->nb_of_philo)
			i = 0;
		else
			i++;
		usleep(500);
	}
}

void	ft_wait_again(t_philo *philos)
{
	while (1)
	{
		pthread_mutex_lock(&philos->args->mutex_philo_in_queue);
		if (philos->args->philo_in_queue == philos->args->nb_of_philo)
		{
			pthread_mutex_unlock(&philos->args->mutex_philo_in_queue);
			break ;
		}
		pthread_mutex_unlock(&philos->args->mutex_philo_in_queue);
		usleep(500);
	}
	usleep(500);
}

void	*visor_routine(void *thread)
{
	t_philo	*philos;
	int		i;
	int		complete;

	philos = (t_philo *)thread;
	i = 0;
	complete = 0;
	ft_wait_again(philos);
	visor_loop(philos, i, complete);
	return (NULL);
}
