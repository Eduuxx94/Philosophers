/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:42:34 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/08 19:33:53 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_threads(t_data *d)
{
	int		i;

	i = -1;
	pthread_mutex_init(&d->run_mutex, NULL);
	gettimeofday(&d->start_time, NULL);
	while (++i < d->var.philos)
	{		
		d->philo[i].d = d;
		d->philo[i].id = i;
		pthread_create(&d->philo[i].thread, 0, &ft_thread_run, (void *)&d->philo[i]); //as threads inicião aqui
	}
	while (--i > -1)
		pthread_join(d->philo[i].thread, NULL);
}

void	*ft_thread_run(void *philo) //cada thread vai iniciar com um id especifico id = index->i;
{
	t_philo	*p;

	p = ((t_philo *)philo);
	//pthread_mutex_lock(&((t_index *)dcopy)->d->run_mutex);
	if (p->d->run)
	{
		printf("%04i Thread n: %i\n", ft_time(p->d), p->id);
	}
	//pthread_mutex_unlock(&((t_index *)dcopy)->d->run_mutex);
	return (0);
}
