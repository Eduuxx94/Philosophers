/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:35:25 by ede-alme          #+#    #+#             */
/*   Updated: 2022/08/04 11:39:49 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "unistd.h"
# include "stdlib.h"
# include "stdio.h"
# include "time.h"
# include "pthread.h"

typedef struct s_var {
	int	philos;
	int	die_t;
	int	eat_t;
	int	sleep_t;
	int	nbr_eats;
}		t_var;

typedef struct s_philo {
	int	id;
	int	forks;
	int	life;
	int	eat_exec;
}		t_philo;

typedef struct s_data {
	t_var	var;
	t_philo	*philo;
}			t_data;

#endif