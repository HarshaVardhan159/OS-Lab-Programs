#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void sort_by_arrival(Process queue[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (queue[j].arrival_time > queue[j + 1].arrival_time) {
                temp = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp;
            }
        }
    }
}

void execute_fcfs(Process queue[], int n, int *current_time) {
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        if (*current_time < queue[i].arrival_time) {
            *current_time = queue[i].arrival_time;
        }
        *current_time += queue[i].burst_time;
        queue[i].completion_time = *current_time;
        queue[i].turnaround_time = queue[i].completion_time - queue[i].arrival_time;
        queue[i].waiting_time = queue[i].turnaround_time - queue[i].burst_time;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", queue[i].pid, queue[i].arrival_time, queue[i].burst_time, queue[i].completion_time, queue[i].turnaround_time, queue[i].waiting_time);
    }
}

int main() {
    int n, system_count = 0, user_count = 0;
    Process system_queue[MAX_PROCESSES], user_queue[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int type;
        Process p;
        printf("Enter process ID, arrival time, burst time, and type (0=System, 1=User) for process %d: ", i + 1);
        scanf("%d %d %d %d", &p.pid, &p.arrival_time, &p.burst_time, &type);

        if (type == 0) {
            system_queue[system_count++] = p;
        } else {
            user_queue[user_count++] = p;
        }
    }

    sort_by_arrival(system_queue, system_count);
    sort_by_arrival(user_queue, user_count);

    int current_time = 0;
    printf("\nExecuting System Processes (Higher Priority - FCFS):\n");
    execute_fcfs(system_queue, system_count, &current_time);

    printf("\nExecuting User Processes (Lower Priority - FCFS):\n");
    execute_fcfs(user_queue, user_count, &current_time);
    printf("Name: Kalaga Harsha Vardhan\nUSN:1BM23CS136");

    return 0;
}
