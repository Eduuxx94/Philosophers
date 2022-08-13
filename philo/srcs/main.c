/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:05:52 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/12 11:46:45 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time(t_data *d)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
			- (d->start_time.tv_sec * 1000 + d->start_time.tv_usec / 1000)));
}

void	ft_exit(char *str, t_data *d, int *exit)
{
	*exit = 1;
	if (d)
	{
		free(d->philo);
	}
	if (str)
		printf("%s", str);
}

int	ft_getint(char *arg, int position, t_data *d)
{
	int			i;
	long long	value;

	i = 0;
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
		value = value + ft_getint(arg, (1 + position), d);
		if (value > 2147483647 && d->exit++)
			ft_exit(NULL, NULL, &d->exit);
	}
	else if (d->exit++)
		ft_exit(NULL, NULL, &d->exit);
	if (position == 0 && value <= 0 && d->exit++)
		ft_exit(NULL, NULL, &d->exit);
	return (value);
}

void	ft_init_values(int argc, char **argv, t_data *d)
{
	d->philo = NULL;
	if ((argc < 5 || argc > 6) && printf("Incorrect number of args...\n"))
		return ;
	d->var.philos = ft_getint(argv[1], 0, d);
	d->var.die_t = ft_getint(argv[2], 0, d);
	d->var.eat_t = ft_getint(argv[3], 0, d);
	d->var.sleep_t = ft_getint(argv[4], 0, d);
	d->var.nbr_eats = 2147483647;
	d->start_time.tv_sec = 0;
	d->run = 0;
	d->anydead = 0;
	if (argc == 6)
		d->var.nbr_eats = ft_getint(argv[5], 0, d);
	d->philo = malloc(sizeof(t_philo) * d->var.philos);
	if (!d->philo && printf("Allocate memory failed\n"))
		return ;
	if (!d->exit)
		ft_init_threads(d);
	else
		printf("Error found\n");
}

int	main(int argc, char **argv)
{
	t_data	d;

	d.philo = NULL;
	d.exit = 0;
	ft_init_values(argc, argv, &d);
	if (d.philo)
		ft_exit(0, &d, &d.exit);
	else
		ft_exit(0, NULL, &d.exit);
	return (0);
}
