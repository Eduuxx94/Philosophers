/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:05:52 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/08 19:21:56 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time(t_data *d)
{
	gettimeofday(&d->current_time, NULL);
	return (((d->current_time.tv_sec * 1000 + d->current_time.tv_usec / 1000)
			- (d->start_time.tv_sec * 1000 + d->start_time.tv_usec / 1000)));
}

void	ft_exit(char *str, t_data *d)
{
	if (d)
	{
		free(d->philo);
		pthread_mutex_destroy(&d->run_mutex);
	}
	if (str)
		printf("%s", str);
}

int	ft_getint(char *arg, int position)
{
	int			i;
	long long	value;

	i = 0;
	if (position == 0 && arg[0] == '0')
		ft_exit("Error, please insert valid argument: >= 1\n", NULL);
	while (arg[i])
		i++;
	i = i - position;
	if (arg[position] == '\0')
		return (0);
	if (arg[position] >= '0' && arg[position] <= '9')
	{
		value = (arg[position] - 48);
		while (i-- >= 2)
			value = value * 10;
		value = value + ft_getint(arg, ++position);
		if (value > 2147483647)
			ft_exit("Error, number input so long...\n", NULL);
	}
	else
		ft_exit("Argument error...\n", NULL);
	return (value);
}

void	ft_init_values(int argc, char **argv, t_data *d)
{
	d->philo = NULL;
	d->tid = -1;
	if (argc < 5 || argc > 6)
		ft_exit("Please insert correct number of args...\n", NULL);
	d->var.philos = ft_getint(argv[1], 0);
	d->var.die_t = ft_getint(argv[2], 0);
	d->var.eat_t = ft_getint(argv[3], 0);
	d->var.sleep_t = ft_getint(argv[4], 0);
	d->var.nbr_eats = 2147483647;
	d->run = 1;
	if (argc == 6)
		d->var.nbr_eats = ft_getint(argv[5], 0);
	d->philo = malloc(sizeof(t_philo) * d->var.philos);
	if (!d->philo)
		ft_exit("Error allocating memory for philo\n", NULL);
	ft_init_threads(d);
}

int	main(int argc, char **argv)
{
	t_data	d;

	d.philo = NULL;
	ft_init_values(argc, argv, &d);
	printf("O numero de philos é %i\n", d.var.philos);
	if (d.philo)
		ft_exit(0, &d);
	else
		ft_exit(0, NULL);
	return (0);
}
