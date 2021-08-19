/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <jmartini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 02:47:24 by jmartini          #+#    #+#             */
/*   Updated: 2021/08/02 02:47:25 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_init_threads_mutexs(t_core *core, t_thread *thread)
{
	int	i;

	i = -1;
	while (++i < core->philo_n)
	{
		thread[i].id = i;
		thread[i].ate = 0;
		thread[i].shared = core;
		pthread_mutex_init(&core->mutex[i], NULL);
		pthread_mutex_init(&thread[i].mutex_death, NULL);
	}
	pthread_mutex_init(&core->mutex_print, NULL);
}

static int	ft_philos_launch(t_core *core, t_thread *thread)
{
	int	i;

	i = -1;
	gettimeofday(&thread->shared->t0, NULL);
	while (++i < core->philo_n)
	{
		if (pthread_create(
				&thread[i].init, NULL, (void *)ft_philo, &thread[i]))
			return (0);
		usleep (10);
	}
	return (1);
}

int	ft_init_main(t_core *core, t_thread *thread)
{
	core->mutex = malloc(sizeof(*core->mutex) * core->philo_n);
	core->forks = malloc(sizeof(*core->forks) * core->philo_n);
	if (!thread || !core->mutex || !core->forks)
		return (0);
	memset(core->forks, 0, core->philo_n);
	ft_init_threads_mutexs(core, thread);
	if (!ft_philos_launch(core, thread))
		return (0);
	return (1);
}
