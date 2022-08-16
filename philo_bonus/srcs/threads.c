/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:42:34 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/15 22:00:29 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_run_threads(t_philo *p)
{
	while (!ft_checkdeath(p) && p->times_eated < p->d->var.nbr_eats)
	{
		if (ft_getforks(p))
		{
			if (!ft_checkdeath(p))
				printf("%05i %02i is eating\n", ft_time(p->d), (p->id + 1));
			p->last_meal = ft_time(p->d);
			while (ft_time(p->d) <= p->d->var.eat_t + p->last_meal)
				if (ft_checkdeath(p))
					return ;
			if (++p->times_eated == p->d->var.nbr_eats && p->d->var.unlimited)
				p->times_eated = 0;
		}
		if (ft_givefork(p))
		{
			if (!ft_checkdeath(p))
				printf("%05i %02i is sleeping\n", ft_time(p->d), (p->id + 1));
			p->last_sleep = ft_time(p->d);
			while (ft_time(p->d) <= p->d->var.sleep_t + p->last_sleep)
				if (ft_checkdeath(p))
					return ;
			if (!ft_checkdeath(p))
				printf("%05i %02i is thinking\n", ft_time(p->d), (p->id + 1));
		}
	}
}

void	*ft_begin(void *philo)
{
	t_philo	*p;

	p = ((t_philo *)philo);
	while ((p->d->var.philos - 1) != p->id || !is_run(p->d, p->id))
	{
		if (p->d->start_time.tv_sec)
			break ;
		if (p->d->var.philos >= 20 && p->d->var.philos <= 500)
			usleep(20000);
		if (p->d->var.philos >= 500)
			usleep(55000);
	}
	p->life = 0 + p->d->var.die_t;
	ft_run_threads(p);
	return (0);
}

void	ft_init_threads(t_data *d)
{
	int		i;

	i = -1;
	pthread_mutex_init(&d->run_lock, NULL);
	while (++i < d->var.philos)
	{
		d->philo[i].d = d;
		d->philo[i].id = i;
		d->philo[i].forks = 1;
		d->philo[i].times_eated = 0;
		pthread_mutex_init(&d->philo[i].mutex, NULL);
		pthread_create(&d->philo[i].thread, 0, &ft_begin, (void *)&d->philo[i]);
	}
	while (--i > -1)
		pthread_join(d->philo[i].thread, NULL);
}
