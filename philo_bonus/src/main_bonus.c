/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <jmartini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 19:03:01 by jmartini          #+#    #+#             */
/*   Updated: 2021/08/04 19:03:02 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static int	ft_init_sem(t_core *core)
{
	sem_unlink("sem_forks");
	sem_unlink("sem_chairs");
	sem_unlink("sem_bin");
	sem_unlink("sem_bin_print");
	core->sem_forks = sem_open(
			"sem_forks", O_CREAT, S_IRWXU, (unsigned int)core->philo_n);
	core->sem_chairs = sem_open(
			"sem_chairs", O_CREAT, S_IRWXU, (unsigned int)core->philo_n - 1);
	core->sem_bin = sem_open(
			"sem_bin", O_CREAT, S_IRWXU, (unsigned int)1);
	core->sem_bin_print = sem_open(
			"sem_bin_print", O_CREAT, S_IRWXU, (unsigned int)1);
	core->pid_arr = malloc(sizeof(*core->pid_arr) * core->philo_n);
	if (core->sem_forks == SEM_FAILED
		|| core->sem_chairs == SEM_FAILED
		|| core->sem_bin == SEM_FAILED
		|| core->sem_bin_print == SEM_FAILED
		|| !core->pid_arr)
		return (0);
	return (1);
}

static int	ft_forker(t_core *core)
{
	int	i;

	i = -1;
	gettimeofday(&core->t0, NULL);
	while (++i < core->philo_n)
	{
		usleep (10);
		core->pid = fork();
		if (core->pid)
			core->pid_arr[i] = core->pid;
		if (core->pid < 0)
			return (0);
		if (!core->pid)
		{
			core->id = i + 1;
			break ;
		}
	}
	return (1);
}

static void	ft_god(t_core *core)
{
	int	i;
	int	wstatus;

	while (waitpid(-1, &wstatus, 0) > 0)
	{
		if (WIFEXITED(wstatus))
		{
			if (!WEXITSTATUS(wstatus))
			{
				i = -1;
				while (++i < core->philo_n)
					kill (core->pid_arr[i], SIGTERM);
				break ;
			}
		}
		usleep (10);
	}
	free(core->pid_arr);
	sem_unlink("sem_forks");
	sem_unlink("sem_chairs");
	sem_unlink("sem_bin");
	sem_unlink("sem_bin_print");
}

int	main(int argc, char **argv)
{
	t_core	core;

	if (!ft_init_args(argc, argv, &core))
		return (0);
	if (!ft_init_sem(&core))
		return (0);
	if (!ft_forker(&core))
		return (0);
	if (!core.pid)
		ft_philo(&core);
	else
		ft_god(&core);
	return (1);
}
