#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_PROCESS 10

int num_of_process;
int execution_time[MAX_PROCESS], deadline[MAX_PROCESS], remain_time[MAX_PROCESS], remain_deadline[MAX_PROCESS];

void get_process_info_EDF() {
    printf("Enter total number of processes (maximum %d): ", MAX_PROCESS);
    scanf("%d", &num_of_process);

    if (num_of_process < 1) {
        printf("Invalid number of processes!\n");
        exit(0);
    }

    for (int i = 0; i < num_of_process; i++) {
        printf("\nProcess %d:\n", i + 1);
        printf("==> Execution time: ");
        scanf("%d", &execution_time[i]);
        printf("==> Deadline: ");
        scanf("%d", &deadline[i]);
        remain_time[i] = execution_time[i];
        remain_deadline[i] = deadline[i];
    }
}

int max_EDF(int a, int b, int c) {
    return (a > b ? (a > c ? a : c) : (b > c ? b : c));
}

int get_observation_time_EDF() {
    int observation_time = 0;
    for (int i = 0; i < num_of_process; i++) {
        observation_time = max_EDF(observation_time, deadline[i], 0);
    }
    return observation_time;
}

void print_schedule_EDF(int process_list[], int cycles) {
    printf("\nScheduling:\n\n");
    printf("Time: ");
    for (int i = 0; i < cycles; i++) {
        printf("| %02d ", i);
    }
    printf("|\n");

    for (int i = 0; i < num_of_process; i++) {
        printf("P[%d]: ", i + 1);
        for (int j = 0; j < cycles; j++) {
            if (process_list[j] == i + 1)
                printf("|####");
            else
                printf("|    ");
        }
        printf("|\n");
    }
}

void calculate_cpu_utilization() {
    float utilization = 0;
    for (int i = 0; i < num_of_process; i++) {
        utilization += (float)execution_time[i] / deadline[i];
    }
    printf("\nCPU Utilization: %.2f%%\n", utilization * 100);
}

void earliest_deadline_first(int time) {
    int process_list[100] = {0};
    int current_process = -1, min_deadline;

    for (int t = 0; t < time; t++) {
        min_deadline = 1000;
        for (int i = 0; i < num_of_process; i++) {
            if (remain_time[i] > 0 && deadline[i] < min_deadline) {
                min_deadline = deadline[i];
                current_process = i;
            }
        }
        if (current_process != -1) {
            process_list[t] = current_process + 1;
            remain_time[current_process]--;

            if (remain_time[current_process] == 0) {
                deadline[current_process] += remain_deadline[current_process];  // Reset deadline for periodic tasks
                remain_time[current_process] = execution_time[current_process];
            }
        }
    }

    print_schedule_EDF(process_list, time);
}

int main() {
    get_process_info_EDF();
    int observation_time = get_observation_time_EDF();
    calculate_cpu_utilization();  // Calculate and print CPU utilization before scheduling
    earliest_deadline_first(observation_time);
    return 0;
}
