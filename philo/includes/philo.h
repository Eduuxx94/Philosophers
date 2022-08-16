/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:35:25 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/16 15:15:51 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "unistd.h"
# include "stdlib.h"
# include "stdio.h"
# include "sys/time.h"
# include "pthread.h"

typedef struct s_data	t_data;

typedef struct s_var {
	int	philos;
	int	die_t;
	int	eat_t;
	int	sleep_t;
	int	nbr_eats;
	int	unlimited;
}		t_var;

typedef struct s_philo {
	t_data			*d;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	int				times_eated;
	int				id;
	int				forks;
	int				life;
	int				last_meal;
	int				last_sleep;
	int				last_thinking;

}		t_philo;

struct s_data {
	int				exit;
	int				anydead;
	t_var			var;
	t_philo			*philo;
	struct timeval	start_time;
	pthread_mutex_t	run_lock;
	int				run;
};

//Main program
int		ft_time(t_data *d);
void	ft_exit(char *str, t_data *d, int *exit);
int		ft_getint(char *arg, int position, t_data *d);
void	ft_init_values(int argc, char **argv, t_data *d);
int		main(int argc, char **argv);

//Threads file functions
void	ft_run_threads(t_philo *p);
void	*ft_begin(void *philo);
void	ft_init_threads(t_data *d);

//utils file functions
int		ft_givefork(t_philo *p);
int		ft_keep_getforks(t_philo *p, int getpear);
int		ft_getforks(t_philo *p);
int		is_run(t_data	*d, int id);
int		ft_checkdeath(t_philo *p);

#endif