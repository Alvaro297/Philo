<h1 align="center">
	📖 Philosophers
</h1>

<p align="center">
  <img src="./philosophersn.png" alt="Philosophers 42 project badge"/>
</p>
---

Philosophers an individual project at [42](https://www.42.fr/42-network/) about introduction to the basics of process threading, and how work on the same memory space.
And learn about mutexes, semaphores, and shared memory.

## Introduction

In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

It was originally formulated in *1965 by Edsger Dijkstra* as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals. Soon after, Tony Hoare gave the problem its present formulation

[More informations](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

*Tips and good methodology to do the project at the bottom of the readme*

## Installation 🖥

To test the project, go to one of the folders __*philo_one*__, __*philo_two*__ or __*philo_three*__ and make a `make`. Then, you can test the project using an executable.

__usage :__

`./philo_one number_philosopher time_to_die time_to_eat time_to_sleep [number_of_time_each_philosophers_must_eat]`
arguments in square brackets are not required (number_of_time_each_philosophers_must_eat)

__exemple :__

`./philo_one 4 500 200 200`

I made a visual option, which makes it possible to have a prettier display, which reduces performance a little.
To use it, add the option __*-v*__ after the executable, this option is only available on __*philo_zero*__ (philo zero is identical to philo one, but it can handle the [-v] option)

__exemple :__

`./philo_zero -v 4 500 200 200`

![alt text](https://zupimages.net/up/20/39/8a98.png)

