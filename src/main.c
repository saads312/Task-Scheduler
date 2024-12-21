#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "task.h"

// the following program is the main file for the task-scheduler project
// the program is a simple task scheduler that allows the user to add, remove, and list tasks
// the program uses a queue to store the tasks, but pre-emption is enabled

queue *foreground;
queue *background;

void run_scheduler() {
    printf("Running tasks in the foreground queue (priority order):\n");
    while (foreground->size > 0) {
        task *t = foreground->tasks[0]; // Highest priority task
        printf("Running Task: %s (ID: %d, Priority: %d)\n", t->name, t->id, t->priority);
        queue_remove(foreground, t->id);
    }

    printf("Running tasks in the background queue (FIFO order):\n");
    while (background->size > 0) {
        task *t = background->tasks[0]; // First-in task
        printf("Running Task: %s (ID: %d, Priority: %d)\n", t->name, t->id, t->priority);
        queue_remove(background, t->id);
    }
}

void add_task() {
    char name[100];
    printf("Enter the task you'd like to add: ");
    scanf(" %[^\n]", name); // Read multi-word task names

    int priority;
    printf("Enter Priority (1-10, 0 for background): ");
    if (scanf("%d", &priority) != 1 || priority < 0 || priority > 10) {
        printf("Invalid priority. Please enter a value between 0 and 10.\n");
        return;
    }

    int id = rand() % 10000; // Generate a random ID
    task *new_task = malloc(sizeof(task));
    new_task->id = id;
    new_task->priority = priority;
    new_task->name = strdup(name);
    new_task->state = READY;
    new_task->function = NULL; // Placeholder
    new_task->arg = NULL;

    if (priority == 0) {
        queue_add(background, new_task);
    } else {
        queue_add(foreground, new_task);
    }

    printf("Task '%s' (ID: %d) added to %s queue.\n", name, id, priority == 0 ? "background" : "foreground");
}

void remove_task() {
    int choice;
    printf("Remove Task by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Invalid choice.\n");
        return;
    }

    if (choice == 1) {
        int id;
        printf("Enter Task ID: ");
        scanf("%d", &id);
        queue_remove(foreground, id);
        queue_remove(background, id);
    } else {
        char name[100];
        printf("Enter Task Name: ");
        scanf(" %[^\n]", name);

        for (int i = 0; i < foreground->size; i++) {
            if (strcmp(foreground->tasks[i]->name, name) == 0) {
                queue_remove(foreground, foreground->tasks[i]->id);
                return;
            }
        }

        for (int i = 0; i < background->size; i++) {
            if (strcmp(background->tasks[i]->name, name) == 0) {
                queue_remove(background, background->tasks[i]->id);
                return;
            }
        }

        printf("Task with name '%s' not found.\n", name);
    }
}

void list_main() {
    printf("Foreground Tasks:\n");
    queue_list(foreground);
    printf("Background Tasks:\n");
    queue_list(background);
}

void display_menu() {
    printf("\n=== Task Scheduler Menu ===\n");
    printf("1. Add Task\n");
    printf("2. Remove Task\n");
    printf("3. List Tasks\n");
    printf("4. Run Scheduler\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    printf("Please enter the maximum number of tasks you'd like to run: ");
    int max_tasks;
    if (scanf("%d", &max_tasks) != 1 || max_tasks <= 0) {
        printf("Invalid input. Exiting program.\n");
        return 1;
    }

    foreground = queue_init(max_tasks, compare_priority);
    background = queue_init(max_tasks, NULL);

    int choice;

    do {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                add_task();
                break;
            case 2:
                remove_task();
                break;
            case 3:
                list_main();
                break;
            case 4:
                run_scheduler();
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    queue_free(foreground);
    queue_free(background);

    return 0;
}
