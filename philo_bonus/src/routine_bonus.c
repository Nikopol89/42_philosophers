/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <jmartini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 22:23:07 by jmartini          #+#    #+#             */
/*   Updated: 2021/08/05 22:23:08 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	ft_fork_get(t_core *core)
{
	sem_wait(core->sem_chairs);
	sem_wait(core->sem_forks);
	ft_status(core, FORK);
	sem_wait(core->sem_forks);
	ft_status(core, FORK);
}

static void	ft_fork_release(t_core *core)
{
	sem_post(core->sem_forks);
	sem_post(core->sem_forks);
	sem_post(core->sem_chairs);
}

static void	ft_grim_reaper(t_core *core)
{
	struct timeval	t1;
	long int		elapsed;

	while (1)
	{
		usleep(10);
		if (!core->simulation)
			return ;
		sem_wait(core->sem_bin);
		gettimeofday(&t1, NULL);
		elapsed = ft_time_elapsed_ms(core->death, t1);
		if (elapsed > core->ttd && core->simulation)
		{
			core->simulation = 0;
			ft_status(core, DEAD);
			exit (0);
		}
		sem_post(core->sem_bin);
	}
}

void	ft_philo(t_core *core)
{
	gettimeofday(&core->death, NULL);
	pthread_create(&core->grim_reaper, NULL, (void *)&ft_grim_reaper, core);
	while (core->ate != core->must_eat && core->simulation)
	{
		ft_fork_get(core);
		sem_wait(core->sem_bin);
		gettimeofday(&core->death, NULL);
		ft_status(core, EAT);
		if (core->must_eat)
			core->ate++;
		sem_post(core->sem_bin);
		ft_timer_ms(core, core->tte);
		ft_fork_release(core);
		if (core->must_eat == core->ate)
			break ;
		ft_status(core, SLEEP);
		ft_timer_ms(core, core->tts);
		ft_status(core, THINK);
	}
	core->simulation = 0;
	pthread_join(core->grim_reaper, NULL);
	free(core->pid_arr);
	exit (1);
}
