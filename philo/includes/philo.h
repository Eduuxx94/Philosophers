/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:35:25 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/06 14:48:07 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "unistd.h"
# include "stdlib.h"
# include "stdio.h"
# include "sys/time.h"
# include "pthread.h"

typedef struct s_var {
	int	philos;
	int	die_t;
	int	eat_t;
	int	sleep_t;
	int	nbr_eats;
}		t_var;

typedef struct s_philo {
	pthread_t		thread;
	pthread_mutex_t	mutex;
	int				id;
	int				forks;
	int				life;
	int				eat_exec;

}		t_philo;

typedef struct s_data {
	t_var			var;
	t_philo			*philo;
	struct timeval	time;
	int				start_time;
	int				run;
	pthread_mutex_t	run_mutex;
}			t_data;

//Main program
void	*ft_thread_run(void *dcopy);
void	ft_exit(char *str, t_data *d);
int		ft_getint(char *arg, int position);
void	ft_init_values(int argc, char **argv, t_data *d);
int		main(int argc, char **argv);

#endif