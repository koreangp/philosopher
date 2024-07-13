/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:22:01 by pscala            #+#    #+#             */
/*   Updated: 2024/07/13 21:18:23 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHER_H
# define PHILOSPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define PINK "\033[38;5;205m"
# define ORANGE "\033[38;5;208m"
# define PURPLE "\033[38;5;93m"
# define LIGHT_BLUE "\033[38;5;81m"
# define LIGHT_GREEN "\033[38;5;120m"
# define RESET "\033[0m"

typedef struct s_args
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_time_to_eat;
	long int		start;
	pthread_mutex_t	printmutex;
}					t_args;

typedef struct s_philo
{
	t_args			*args;
	int				id;
	pthread_mutex_t	fork;
	pthread_mutex_t	mealsmutex;
	pthread_mutex_t	*nextfork;
	pthread_t		thread;
	long int		last_meal;
	int				nb_of_meals;

}					t_philo;

int					ft_atoi(const char *str);
int					ft_strlen(char *str);
int					ft_isdigit(int c);
int					is_alnum(char *str);
int					is_good_int(char *str);
int					ft_pars(char **av);
int					init_args(t_args *args, char **av, int ac);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

#endif