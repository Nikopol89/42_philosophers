/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <jmartini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 01:23:54 by jmartini          #+#    #+#             */
/*   Updated: 2021/08/05 01:23:55 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

enum	e_err {
	ERR_ARG,
	ERR_EAT,
	ERR_PHILO,
};
static const char *const	g_err_str[] = {
	"Bad arguments",
	"number_of_times_each_philosopher_must_eat set to 0",
	"number_of_philosophers can not be 0",
};

static int	ft_error_return(int err)
{
	printf("Error : %s\n", g_err_str[err]);
	return (0);
}

static int	ft_arg_limit(char *arg)
{
	char	*limit;
	int		i;

	limit = "2147483647";
	i = -1;
	while (arg[++i])
	{
		if (arg[i] > limit[i])
			return (0);
	}
	return (1);
}

static int	ft_args_check(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (0);
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			if (j > 10)
				return (0);
		}
		if (j == 10 && !ft_arg_limit(argv[i]))
			return (0);
	}
	return (1);
}

int	ft_init_args(int argc, char **argv, t_core *core)
{
	if (!ft_args_check(argc, argv))
		return (ft_error_return(ERR_ARG));
	core->philo_n = ft_atoi_ns(argv[1]);
	if (!core->philo_n)
		return (ft_error_return(ERR_PHILO));
	core->ttd = ft_atoi_ns(argv[2]);
	core->tte = ft_atoi_ns(argv[3]);
	core->tts = ft_atoi_ns(argv[4]);
	core->must_eat = -1;
	core->simulation = 1;
	core->ate = 0;
	if (argc == 6)
		core->must_eat = ft_atoi_ns(argv[5]);
	if (!core->must_eat)
		return (ft_error_return(ERR_EAT));
	return (1);
}
