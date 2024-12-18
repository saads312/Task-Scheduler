#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// this file defines the task struct and the task queue struct,
// as well as the functions to manipulate them

// the state enum represents the state of a task
typedef enum {
    READY,
    RUNNING,
    BLOCKED,
    TERMINATED
} state;

// the task struct represents a task in the task scheduler
typedef struct task {
    int id; // the id of the task
    int priority; // the priority of the task
    state state; // the state of the task
    void (*function)(void * arg); // a function pointer to the task's function
    void * arg; // the argument to the task's function
} task;

// the task queue struct represents a queue of tasks 
typedef struct queue{
    task **tasks; // the tasks in the queue
    int size; // the number of tasks in the queue
    int capacity; // the capacity of the queue
    int (*compare)(task * a, task * b); // a function pointer to compare tasks
} queue;

// task queue functions
queue * task_queue_init(int capacity, int (*comparator)(task * a, task * b));
void task_queue_free(queue * q);
void task_queue_add(queue * q, task * t);
void task_queue_remove(queue * q, int id);
void task_queue_list(queue * q);
void compare_priority(task * a, task * b);

