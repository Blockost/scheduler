# Specification

## Table of contents
* Introduction
* Specs
* How to implement
* Enhancements
* Conclusion

## Introduction
### Subject definition
As part of GSI Project of the second year of engineering, we will produce a _scheduler_ that will schedule different 
processes in several strategies.
### Objectives
The objective is for us to realize this project with rigor, annotated and documented code. We will try to develop a
rapid and effective application, with the most possible additional features.

## Specs
As explained by the customer, the project goal is to retrieve a queue with multiple tasks to redirect.
The redirection should be based on the size of the task.
All of these tasks will be allocated a portion of a CPU core in order to perform.

## How to implement
To implement this scheduler, we will use C++ with OpenMP and MPI libraries. Network connections will be made with IPv6 
protocol, and the source code will be shared on the school GitLAB. Our group will use the Integrated Development Environment
(IDE) __CLion__ (JetBrains) for any writing source code and sharing.
For each _thread_ (one per processor), we will pick a task from the task _pool_ that we have generated first, then we 
will remove the task from it. We will implement the task and will wait until a new task is available. The program stops 
when there is no more task in the task _pool_.

## Enhancements
If we have time after planting the main features, we will choose to develop a control interface somewhat more developed 
in the first place. We will thereafter manage a little better resources by introducing a _timeout_ for all managed tasks,
which will be killed if they exceed this period of time. Then we will develop prioritization of tasks: priority will be 
assigned to the tasks and the most important will be executed first.

## Conclusion
* To conclude ? Really...?