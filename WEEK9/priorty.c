#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int arrival_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int is_completed;
};

int main() {
    int n, time = 0, completed = 0;
    float total_TAT = 0, total_WT = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time, Burst Time & Priority for Process %d: ", p[i].id);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].is_completed = 0;
    }

    while (completed < n) {
        int idx = -1, highest_priority = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].is_completed) {
                if (p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == highest_priority) {
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            time += p[idx].burst_time;
            p[idx].completion_time = time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            total_TAT += p[idx].turnaround_time;
            total_WT += p[idx].waiting_time;
            p[idx].is_completed = 1;
            completed++;
        } else {
            time++;
        }
    }

    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i].id, p[i].arrival_time, p[i].burst_time,
               p[i].priority, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("\nAverage Turnaround Time = %.2f", total_TAT / n);
    printf("\nAverage Waiting Time = %.2f\n", total_WT / n);

    return 0;
}
