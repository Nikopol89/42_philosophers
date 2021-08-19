/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_unsafe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <jmartini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 02:47:20 by jmartini          #+#    #+#             */
/*   Updated: 2021/08/02 02:47:21 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** THIS VERSION IS NOT DEADLOCK SAFE
** DEMO ONLY FOR SIMULATION BENCHMARKS
*/

#include "../inc/philo.h"

static void	ft_fork_get_next(t_thread *thread)
{
	if (thread->id == thread->shared->philo_n - 1)
	{
		pthread_mutex_lock(&thread->shared->mutex[0]);
		thread->shared->forks[0] = 1;
		ft_status(thread, FORK);
	}
	else
	{
		pthread_mutex_lock(&thread->shared->mutex[thread->id + 1]);
		thread->shared->forks[thread->id + 1] = 1;
		ft_status(thread, FORK);
	}
}

static void	ft_fork_get(t_thread *thread)
{
	pthread_mutex_lock(&thread->shared->mutex[thread->id]);
	thread->shared->forks[thread->id] = 1;
	ft_status(thread, FORK);
	ft_fork_get_next(thread);
}

static void	ft_fork_release(t_thread *thread)
{
	thread->shared->forks[thread->id] = 0;
	pthread_mutex_unlock(&thread->shared->mutex[thread->id]);
	if (thread->id == thread->shared->philo_n - 1)
	{
		thread->shared->forks[0] = 0;
		pthread_mutex_unlock(&thread->shared->mutex[0]);
	}
	else
	{
		thread->shared->forks[thread->id + 1] = 0;
		pthread_mutex_unlock(&thread->shared->mutex[thread->id + 1]);
	}
}

static void	ft_grim_reaper(t_thread *thread)
{
	struct timeval	t1;
	long int		elapsed;

	while (1)
	{
		usleep(10);
		if (!thread->shared->simulation)
			return ;
		pthread_mutex_lock(&thread->mutex_death);
		gettimeofday(&t1, NULL);
		elapsed = ft_time_elapsed_ms(thread->death, t1);
		if (elapsed > thread->shared->ttd
			&& thread->shared->simulation
			&& thread->ate != thread->shared->must_eat)
		{
			thread->shared->simulation = 0;
			ft_status(thread, DEAD);
		}
		pthread_mutex_unlock(&thread->mutex_death);
	}
}

void	ft_philo(t_thread *thread)
{
	gettimeofday(&thread->death, NULL);
	pthread_create(&thread->grim_reaper, NULL, (void *)ft_grim_reaper, thread);
	while (thread->ate != thread->shared->must_eat
		&& thread->shared->simulation)
	{
		ft_fork_get(thread);
		pthread_mutex_lock(&thread->mutex_death);
		gettimeofday(&thread->death, NULL);
		ft_status(thread, EAT);
		if (thread->shared->must_eat)
		{
			thread->ate++;
			thread->shared->have_eaten++;
		}
		pthread_mutex_unlock(&thread->mutex_death);
		ft_timer_ms(thread, thread->shared->tte);
		ft_fork_release(thread);
		ft_status(thread, SLEEP);
		ft_timer_ms(thread, thread->shared->tts);
		ft_status(thread, THINK);
	}
	pthread_join(thread->grim_reaper, NULL);
}
