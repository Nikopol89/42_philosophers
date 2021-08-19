/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <jmartini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 02:47:41 by jmartini          #+#    #+#             */
/*   Updated: 2021/08/02 02:47:42 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

enum	e_status {
	DEAD,
	FORK,
	EAT,
	SLEEP,
	THINK,
};
static const char *const	g_status_str[] = {
	"\e[31mis DEAD\e[0m",
	"has taken a fork",
	"\e[32mis eating\e[0m",
	"\e[35mis sleeping\e[0m",
	"\e[34mis thinking\e[0m",
};

typedef struct s_core
{
	int				philo_n;
	int				ttd;
	int				tte;
	int				tts;
	int				must_eat;
	int				have_eaten;
	int				simulation;
	int				*forks;
	struct timeval	t0;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex_print;
}					t_core;

typedef struct s_thread
{
	int				id;
	int				ate;
	pthread_t		init;
	pthread_t		grim_reaper;
	pthread_mutex_t	mutex_death;
	struct timeval	death;
	t_core			*shared;
}					t_thread;

/* INIT */
int			ft_init_args(int argc, char **argv, t_core *core);
int			ft_init_main(t_core *core, t_thread *thread);

/* ROUTINE */
void		ft_philo(t_thread *thread);

/* UTILS */
void		ft_status(t_thread *thread, int status);
long int	ft_time_elapsed_ms(struct timeval t0, struct timeval t1);
void		ft_timer_ms(t_thread *thread, long int delay);
int			ft_isdigit(int c);
int			ft_atoi_ns(const char *str);

#endif