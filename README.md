# Philosophers

This code defines several functions related to the behavior of philosophers. The ft_init_threads function initializes the data for a number of philosophers specified in the t_data struct d, which is passed as an argument. For each philosopher, the function creates a new thread and starts it with the ft_begin function, which is passed the address of a t_philo struct.

The ft_begin function waits for all philosophers to start, then sets the life of each philosopher to the value of d->var.die_t and calls the ft_run_threads function. The ft_run_threads function implements the behavior of a single philosopher and runs until the philosopher has eaten the specified number of times or the ft_checkdeath function returns true.

In each iteration of ft_run_threads, the philosopher attempts to obtain two forks with the ft_getforks function and eat if successful. Then, the philosopher releases the forks and goes to sleep for a specified time with the ft_givefork function. After waking up, the philosopher thinks for a specified amount of time with the ft_think function before attempting to eat again.

Throughout the code, the ft_checkdeath function is used to check if a philosopher is still alive. The ft_time function returns the current time and the ft_givefork and ft_getforks functions handle the acquiring and releasing of forks by a philosopher.

In this code, the mutex is used to ensure that only one philosopher can access a fork at a time, as forks represent shared resources that multiple philosophers might try to access simultaneously. The mutex is also used to synchronize access to the ft_run_threads() function, which is the main function for each philosopher thread. By using a mutex, the code can ensure that only one philosopher thread runs the ft_run_threads() function at a time, preventing race conditions and ensuring a consistent state of the shared resources.

In the code, pthread_mutex_init() is used to initialize a mutex, and pthread_mutex_destroy() is used to clean up a mutex when it is no longer needed. pthread_mutex_lock() and pthread_mutex_unlock() are used to lock and unlock the mutex, respectively.
