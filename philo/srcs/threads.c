/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:42:34 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/12 22:21:30 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_getforks(t_philo *p)
{
	int	getpear;

	getpear = 0;
	if (p->d->var.philos == 1)
		return (0);
	if (p->id != (p->d->var.philos - 1))
		getpear = p->id + 1;
	//pthread_mutex_lock(&p->mutex);
	//pthread_mutex_lock(&p->d->philo[getpear].mutex);
	if (p->forks == 1 && p->d->philo[getpear].forks == 1)
	{
		pthread_mutex_lock(&p->d->run_lock);
		p->forks++;
		p->d->philo[getpear].forks--;
		pthread_mutex_unlock(&p->d->run_lock);
		return (1);
	}
	//pthread_mutex_unlock(&p->d->philo[getpear].mutex);
	//pthread_mutex_unlock(&p->mutex);
	return (0);
}

int	ft_checkdeath(t_philo *p)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&p->d->run_lock);
	if (p->life < ft_time(p->d) && !p->d->anydead)
	{
		p->d->anydead = 1;
		printf("%05i	%02i	died\n", ft_time(p->d), p->id);
	}
	result = p->d->anydead;
	pthread_mutex_unlock(&p->d->run_lock);
	return (result);
}

void	ft_run_threads(t_philo *p)
{
	if (!ft_checkdeath(p))
	{
		//pthread_mutex_lock(&p->d->run_lock);
		if (ft_getforks(p))
		{
			printf("%i Pegou os talheres\n", p->id);
			return ;
		}
		else
			printf("%i Tentou pegar os talheres\n", p->id);
		usleep(20);
		//pthread_mutex_unlock(&p->d->run_lock);
	}
	else
		return ;
	ft_run_threads(p);
}

int	is_run(t_data	*d, int id)
{
	int	i;

	printf("Passou por aqui\n");
	pthread_mutex_lock(&d->run_lock);
	if (id == (d->var.philos - 1))
	{
		gettimeofday(&d->start_time, NULL);
		d->run = 1;
	}
	i = d->run;
	pthread_mutex_unlock(&d->run_lock);
	return (i);
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
		pthread_mutex_init(&d->philo[i].mutex, NULL);
		pthread_create(&d->philo[i].thread, 0, &ft_begin, (void *)&d->philo[i]);
	}
	while (--i > -1)
		pthread_join(d->philo[i].thread, NULL);
}
