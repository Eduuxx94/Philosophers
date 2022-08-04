/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:05:52 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/04 11:43:30 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(char *str, t_data *d)
{
	if (d->philo)
		free(d->philo);
	if (str)
		printf("%s", str);
	exit(0);
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
		value = value + ft_getint(arg, ++position, d);
		if (value > 2147483647)
			ft_exit("Error, number input so long...\n", d);
	}
	else
		ft_exit("Argument error...\n", d);
	return (value);
}

int	main(int argc, char **argv)
{
	t_data	d;

	if (argc < 5 || argc > 6)
		ft_exit("Please insert correct number of args...\n", NULL);
	d.var.philos = ft_getint(argv[1], 0, NULL);
	d.var.die_t = ft_getint(argv[2], 0, NULL);
	d.var.eat_t = ft_getint(argv[3], 0, NULL);
	d.var.sleep_t = ft_getint(argv[4], 0, NULL);
	d.var.nbr_eats = 2147483647;
	if (argc == 6)
		d.var.nbr_eats = ft_getint(argv[5], 0, NULL);
	d.philo = malloc(sizeof(t_philo *) * d.var.philos);
	printf("O numero de philos: %i\n", d.var.philos);
	printf("O tempo para morrer: %i\n", d.var.die_t);
	printf("O tempo para comer: %i\n", d.var.eat_t);
	printf("O tempo para dormir: %i\n", d.var.sleep_t);
	if (argc == 6)
		printf("Refeições permitidas %i\n", d.var.nbr_eats);
	ft_exit(0, &d);
	return (0);
}
