/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:05:52 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/04 16:59:39 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_thread_run(void *dcopy) /*dcopy é um endereço de uma estrutura passada como argumento do tipo void. */
{
	t_data	*d; //struct d vai usar o endereço do dcopy e vais subscresver o tipo void por t_data.

	d = dcopy;
	if (d)
		printf("Numero de threads: %i\n", d->var.philos);
	return (0);
}

void	ft_exit(char *str, t_data *d)
{
	if (d)
		free(d->philo);
	if (str)
		printf("%s", str);
	exit(0);
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
	int				i;

	i = -1;
	d->philo = NULL;
	if (argc < 5 || argc > 6)
		ft_exit("Please insert correct number of args...\n", NULL);
	d->var.philos = ft_getint(argv[1], 0);
	d->var.die_t = ft_getint(argv[2], 0);
	d->var.eat_t = ft_getint(argv[3], 0);
	d->var.sleep_t = ft_getint(argv[4], 0);
	d->var.nbr_eats = 2147483647;
	if (argc == 6)
		d->var.nbr_eats = ft_getint(argv[5], 0);
	d->philo = malloc(sizeof(t_philo) * d->var.philos);
	if (!d->philo)
		ft_exit("Error allocating memory for philo\n", NULL);
	while (++i < d->var.philos)
		pthread_create(&d->philo[i].thread, NULL, &ft_thread_run, (void *)d);
	while (--i > -1)
		pthread_join(d->philo[i].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_data	d;

	d.philo = NULL;
	ft_init_values(argc, argv, &d);
	printf("O numero de philos é %i\n", d.var.philos);
	ft_exit(0, &d);
	return (0);
}
