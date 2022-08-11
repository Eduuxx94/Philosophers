/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:42:34 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/11 11:46:27 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_run_threads(t_philo *p)
{
	//while (p)
	//{
		printf("%04i	ID: %02i\n", ft_time(p->d), p->id);
		usleep(20);
	//}
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
		//usleep(20000);
	}
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
		pthread_create(&d->philo[i].thread, 0, &ft_begin, (void *)&d->philo[i]);
	}
	while (--i > -1)
		pthread_join(d->philo[i].thread, NULL);
}
