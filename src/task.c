#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "task.h"

/**
 * Queue Initialization: The queue_init function initializes a new queue with the given capacity and comparator function.
 * @param capacity the capacity of the queue
 * @param comparator the comparator function to compare tasks (NULL for FIFO behavior)
 * @return pointer to the initialized queue
 */
queue *queue_init(int capacity, int (*comparator)(task * a, task * b)) {
    queue * q = malloc(sizeof(queue));
    q->tasks = malloc(capacity * sizeof(task *));
    q->size = 0;
    q->capacity = capacity;
    q->compare = comparator;
    return q;
}

/**
 * Queue Free: The queue_free function frees the memory allocated for the queue and its tasks.
 * @param q the queue to free
 * @return void
 */
void queue_free(queue * q) {
    for (int i = 0; i < q->size; i++) {
        free(q->tasks[i]);
    }
    free(q->tasks);
    free(q);
}

/**
 * Queue Add: The queue_add function adds a task to the queue based on its priority.
 * @param q the queue to add the task to
 * @param t the task to add
 * @return void
 */
void queue_add(queue * q, task * t) {
    if (q->size == q->capacity) {
        printf("Max number of tasks running, cannot add task\n");
        return;
    }

    if (q->compare == NULL) {
        q->tasks[q->size++] = t;
        return;
    }

    int i = q->size - 1;
    while (i >= 0 && q->compare(q->tasks[i], t) > 0 && q->compare != NULL) {
        q->tasks[i + 1] = q->tasks[i];
        i--;
    }

    q->tasks[i+1] = t;
    q->size++;
}

/**
 * Queue Remove: The queue_remove function removes a task from the queue based on its id.
 * @param q the queue to remove the task from
 * @param id the id of the task to remove
 * @return void
 */
void queue_remove(queue * q, int id) {
    for (int i = 0; i < q->size; i++) {
        if (q->tasks[i]->id == id) {
            free(q->tasks[i]);
            for (int j = i; j < q->size - 1; j++) {
                q->tasks[j] = q->tasks[j + 1];
            }
            q->size--;
            return;
        }
    }
    fprintf(stderr, "Task with id %d not found\n", id);
}

/**
 * Queue List: The queue_list function lists the tasks in the queue.
 * @param q the queue to list
 * @return void
 */
void queue_list(queue * q) {
    for (int i = 0; i < q->size; i++) {
        printf("Task %d: priority %d\n", q->tasks[i]->id, q->tasks[i]->priority);
    }
}

/**
 * Compare Priority: The compare_priority function compares two tasks based on their priority.
 * @param new the new task to compare
 * @param comparison the task to compare to
 * @return the difference in priority between the two tasks
 */
int compare_priority(task * new, task * comparison) {
    return comparison->priority - new->priority;
}

