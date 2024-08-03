/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:22:01 by pscala            #+#    #+#             */
/*   Updated: 2024/08/03 16:28:33 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[38;5;226m"
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
	int				dead;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_time_to_eat;
	int				countp;
	long int		start;
	int				flag;
	pthread_mutex_t	mutex_countp;
	pthread_mutex_t	printmutex;
	pthread_mutex_t	deadmutex;
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
void				*routine(void *thread);
void				*visor_routine(void *thread);
int					creat_threads(t_philo *philos, t_args *args);
void				ft_wait_again(t_philo *philos);
void				visor_loop(t_philo *philos, int i, int complete);
int					check_if_dead(t_philo *philo);
void				ft_sleep(long int time_usleep);
int					eating(t_philo *philo);
int					sleep_and_think(t_philo *philo);
int					grab_and_eat(t_philo *philo);
void				ft_wait_everyone(t_philo *philo);
int					philo_pos(t_philo *philo);
int					case_one_philo(t_philo *philo);
int					is_he_dead(t_philo *philo);
void				ft_print(t_philo *philo, char *str, char *color);
int					init_args(t_args *args, char **av, int ac);
int					init_tab_philos(t_philo **philos, t_args *args);
long int			get_time(void);

#endif