#include <stdio.h>
#include <string.h>
typedef struct {
    int id;
    char description[50];
    int priority; 
    int isCompleted; 
} Task;
void displayTask(Task t) {
    printf("ID: %d, Description: %s, Priority: %d, Completed: %s\n",
           t.id, t.description, t.priority, t.isCompleted ? "Yes" : "No");
}
int main() {
    Task tasks[3]; 
    tasks[0].id = 1;
    strcpy(tasks[0].description, "Prepare presentation");
    tasks[0].priority = 1; 
    tasks[0].isCompleted = 0; 
    tasks[1].id = 2;
    strcpy(tasks[1].description, "Send weekly report");
    tasks[1].priority = 2; 
    tasks[1].isCompleted = 0; 
    tasks[2].id = 3;
    strcpy(tasks[2].description, "Review project documentation");
    tasks[2].priority = 3; 
    tasks[2].isCompleted = 0; 
    printf("--- Initial Task List ---\n");
    int i;
    for (i = 0; i < 3; i++) {
        displayTask(tasks[i]);
    }
    printf("\n");
    int taskIdToComplete = 2;
    printf("--- Marking Task ID %d as Completed ---\n", taskIdToComplete);
    for (i = 0; i < 3; i++) {
        if (tasks[i].id == taskIdToComplete) {
            tasks[i].isCompleted = 1;
            break; 
        }
    }
    printf("\n");
    printf("--- Updated Task List ---\n");
    for (i = 0; i < 3; i++) {
        displayTask(tasks[i]);
    }
    return 0;
}