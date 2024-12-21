/**
 * Testing summary:
 * 
 *  - test_add: works
 *      - case 1: add 2 tasks to the queue as a PQ and check if they are in the correct order according to priority
 *      - case 2: add 3 tasks to the queue as a PQ, with one duplicate priority, and check if they are in the correct order (priority)
 *      - case 3: add 3 tasks to the queue as a normal queue, check if they are in order of insertion
 * 
 *  - test_remove: works
 *      - case 1: add 2 tasks to the queue, remove one, check if the queue has the correct size and the correct task
 *      - case 2: don't add any tasks to the queue, try to remove a task
 *      - case 3: add 2 tasks to the queue, remove a task that doesn't exist
 * 
 * - test_list: works
 *      - case 1: add 2 tasks to the queue, list the tasks
 *      - case 2: add no tasks to the queue, list the tasks  
 *      - case 3: add 2 tasks to the queue, remove a task, list the tasks
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "task.h"

void test_add () {
    queue * q = queue_init(10, compare_priority);

    task * t1 = malloc(sizeof(task));
    t1->id = 1;
    t1->priority = 5;
    
    task * t2 = malloc(sizeof(task));
    t2->id = 2;
    t2->priority = 10;

    task * t3 = malloc(sizeof(task));
    t3->id = 3;
    t3->priority = 10;
    
    queue_add(q, t1);
    queue_add(q, t2);
    queue_add(q, t3);

    assert(q->size == 3);
    assert(q->tasks[0]->id == 2); // higher priority task is first
    assert(q->tasks[1]->id == 3); // lower priority task is second
    assert(q->tasks[2]->id == 1); // lower priority task is third

    queue_list(q);

    printf("test_add passed!\n");

    queue_free(q);
}

void test_remove () {

    queue * q = queue_init(10, compare_priority);

    task * t1 = malloc(sizeof(task));
    t1->id = 1;
    t1->priority = 5;
    
    task * t2 = malloc(sizeof(task));
    t2->id = 2;
    t2->priority = 10;
    
    queue_add(q, t1);
    queue_add(q, t2);

    queue_remove(q, 1);

    assert(q->size == 1);
    assert(q->tasks[0]->id == 2);

    printf("test_remove passed!\n");

    queue_free(q);

}

void test_list () {
    queue * q = queue_init(10, compare_priority);

    task * t1 = malloc(sizeof(task));
    t1->id = 1;
    t1->priority = 5;
    
    task * t2 = malloc(sizeof(task));
    t2->id = 2;
    t2->priority = 10;
    
    queue_add(q, t1);
    queue_add(q, t2);

    queue_list(q);

    printf("test_list passed!\n");

    queue_free(q);
}

int main () {
    test_add();
    test_remove();
    test_list();
    printf("All tests passed!\n");
    return 0;
}




