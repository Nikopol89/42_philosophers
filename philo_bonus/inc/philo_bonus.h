/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <jmartini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 19:03:06 by jmartini          #+#    #+#             */
/*   Updated: 2021/08/04 19:03:07 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>
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
	int				simulation;
	sem_t			*sem_forks;
	sem_t			*sem_chairs;
	sem_t			*sem_bin;
	sem_t			*sem_bin_print;
	pid_t			*pid_arr;
	pid_t			pid;
	struct timeval	t0;
	int				id;
	int				ate;
	struct timeval	death;
	pthread_t		grim_reaper;
}					t_core;

/* INIT */
int			ft_init_args(int argc, char **argv, t_core *core);

/* ROUTINE */
void		ft_philo(t_core *core);

/* UTILS */
void		ft_status(t_core *core, int status);
long int	ft_time_elapsed_ms(struct timeval t0, struct timeval t1);
void		ft_timer_ms(t_core *core, long int delay);
int			ft_isdigit(int c);
int			ft_atoi_ns(const char *str);

#endif