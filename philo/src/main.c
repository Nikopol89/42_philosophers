/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <jmartini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 02:47:13 by jmartini          #+#    #+#             */
/*   Updated: 2021/08/02 02:47:14 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_garbage_collector(t_core *core, t_thread *thread)
{
	int	i;

	i = -1;
	while (++i < core->philo_n)
	{
		if (core->philo_n == 1)
		{
			pthread_join(thread[i].grim_reaper, NULL);
			pthread_detach(thread[i].init);
		}
		pthread_join(thread[i].init, NULL);
	}
	free (thread);
	free (core->forks);
	free (core->mutex);
}

static void	ft_god(t_core *core, t_thread *thread)
{
	while (1)
	{
		usleep(10);
		if (core->have_eaten == core->must_eat * core->philo_n)
			core->simulation = 0;
		if (core->simulation == 0)
		{
			ft_garbage_collector(core, thread);
			return ;
		}
	}
}

int	main(int argc, char **argv)
{
	t_core		core;
	t_thread	*thread;

	if (!ft_init_args(argc, argv, &core))
		return (0);
	thread = malloc(sizeof(*thread) * core.philo_n);
	if (!ft_init_main(&core, thread))
		return (0);
	ft_god(&core, thread);
	return (1);
}
