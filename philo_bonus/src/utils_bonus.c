/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <jmartini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 01:23:57 by jmartini          #+#    #+#             */
/*   Updated: 2021/08/05 01:23:58 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	ft_status(t_core *core, int status)
{
	struct timeval	t1;
	long int		elapsed;

	sem_wait(core->sem_bin_print);
	gettimeofday(&t1, NULL);
	elapsed = ft_time_elapsed_ms(core->t0, t1);
	if (elapsed)
		elapsed += 1;
	if (core->simulation || status == DEAD)
		printf("[%ld]\t%.2d %s\n", elapsed, core->id, g_status_str[status]);
	if (status != DEAD)
		sem_post(core->sem_bin_print);
}

void	ft_timer_ms(t_core *core, long int delay)
{
	struct timeval	time;
	long int		goal;

	gettimeofday(&time, NULL);
	goal = time.tv_sec * 1000 + time.tv_usec / 1000 + delay;
	while (goal > (time.tv_sec * 1000 + time.tv_usec / 1000)
		&& core->simulation)
	{
		usleep (1);
		gettimeofday(&time, NULL);
	}
}

long int	ft_time_elapsed_ms(struct timeval t0, struct timeval t1)
{
	long int	elapsed;

	elapsed = (t1.tv_sec - t0.tv_sec) * 1000.0;
	elapsed += (t1.tv_usec - t0.tv_usec) / 1000.0;
	return (elapsed);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi_ns(const char *str)
{
	int	it;
	int	sign;
	int	n;

	it = 0;
	sign = 1;
	n = 0;
	if (str[it] == '-' && ft_isdigit(str[it + 1]))
	{
		sign = -1;
		it++;
	}
	if (str[it] == '+' && ft_isdigit(str[it + 1]))
		it++;
	while (ft_isdigit(str[it]))
	{
		n = (n * 10) + (str[it] - '0');
		it++;
	}
	return (n * sign);
}
