/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:59:24 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/16 15:15:36 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_givefork(t_philo *p)
{
	int	getpear;

	getpear = 0;
	if (p->id != (p->d->var.philos - 1))
		getpear = p->id + 1;
	pthread_mutex_lock(&p->mutex);
	if (p->forks == 2 && p->forks--)
	{
		pthread_mutex_unlock(&p->mutex);
		pthread_mutex_lock(&p->d->philo[getpear].mutex);
		p->d->philo[getpear].forks++;
		pthread_mutex_unlock(&p->d->philo[getpear].mutex);
		return (1);
	}
	else
		pthread_mutex_unlock(&p->mutex);
	return (0);
}

int	ft_keep_getforks(t_philo *p, int getpear)
{
	if (!ft_checkdeath(p))
		printf("%i %i has taken a fork\n", ft_time(p->d), (p->id + 1));
	p->life = (ft_time(p->d) + p->d->var.die_t);
	pthread_mutex_unlock(&p->d->philo[getpear].mutex);
	return (1);
}

int	ft_getforks(t_philo *p)
{
	int	getpear;

	getpear = 0;
	if (p->id != (p->d->var.philos - 1))
		getpear = p->id + 1;
	pthread_mutex_lock(&p->mutex);
	if (p->d->var.philos > 1 && p->forks == 1 && p->forks++)
	{
		pthread_mutex_unlock(&p->mutex);
		pthread_mutex_lock(&p->d->philo[getpear].mutex);
		if (p->d->philo[getpear].forks == 1 && p->d->philo[getpear].forks--)
			return (ft_keep_getforks(p, getpear));
		else
		{
			pthread_mutex_unlock(&p->d->philo[getpear].mutex);
			pthread_mutex_lock(&p->mutex);
			p->forks--;
			pthread_mutex_unlock(&p->mutex);
		}
	}
	else
		pthread_mutex_unlock(&p->mutex);
	return (0);
}

int	is_run(t_data	*d, int id)
{
	int	i;

	pthread_mutex_lock(&d->run_lock);
	if (id == d->var.philos - 1)
	{
		gettimeofday(&d->start_time, NULL);
		d->run = 1;
	}
	pthread_mutex_unlock(&d->run_lock);
	i = d->run;
	return (i);
}

int	ft_checkdeath(t_philo *p)
{
	int	result;

	pthread_mutex_lock(&p->d->run_lock);
	if (!p->d->anydead && p->life < ft_time(p->d))
	{
		p->d->anydead = 1;
		pthread_mutex_unlock(&p->d->run_lock);
		printf("%i %i died\n", ft_time(p->d), (p->id + 1));
		return (1);
	}
	result = p->d->anydead;
	pthread_mutex_unlock(&p->d->run_lock);
	return (result);
}
