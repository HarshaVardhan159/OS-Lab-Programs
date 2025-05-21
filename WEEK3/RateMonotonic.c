#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAX_PROCESS 10

int num_of_process;
int execution_time[MAX_PROCESS], period[MAX_PROCESS], remain_time[MAX_PROCESS];

void get_process_info() {
    printf("Enter total number of processes (maximum %d): ", MAX_PROCESS);
    scanf("%d", &num_of_process);

    for (int i = 0; i < num_of_process; i++) {
        printf("\nProcess %d:\n", i + 1);
        printf("==> Execution time: ");
        scanf("%d", &execution_time[i]);
        printf("==> Period: ");
        scanf("%d", &period[i]);
        remain_time[i] = execution_time[i];
    }
}

int max(int a, int b, int c) {
    return (a > b ? (a > c ? a : c) : (b > c ? b : c));
}

int get_observation_time() {
    int observation_time = 0;
    for (int i = 0; i < num_of_process; i++) {
        observation_time = max(observation_time, period[i], 0);
    }
    return observation_time;
}

void print_schedule(int process_list[], int cycles) {
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

void rate_monotonic(int time) {
    int process_list[100] = {0};
    float utilization = 0;

    for (int i = 0; i < num_of_process; i++) {
        utilization += (1.0 * execution_time[i]) / period[i];
    }

    int n = num_of_process;
    float m = n * (pow(2, 1.0 / n) - 1);

    if (utilization > m) {
        printf("\nThe given processes are not schedulable under Rate Monotonic.\n");
        return;
    }

    for (int i = 0; i < time; i++) {
        int min = 1000, next_process = -1;

        for (int j = 0; j < num_of_process; j++) {
            if (remain_time[j] > 0 && period[j] < min) {
                min = period[j];
                next_process = j;
            }
        }

        if (next_process != -1) {
            process_list[i] = next_process + 1;
            remain_time[next_process]--;

            if ((i + 1) % period[next_process] == 0) {
                remain_time[next_process] = execution_time[next_process];
            }
        }
    }

    print_schedule(process_list, time);
}

int main() {
    get_process_info();
    int observation_time = get_observation_time();
    rate_monotonic(observation_time);
    return 0;
}
