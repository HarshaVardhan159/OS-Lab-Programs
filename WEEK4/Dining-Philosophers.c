#include <stdio.h>
#include <windows.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (i + 4) % N
#define RIGHT (i + 1) % N

int state[N];
int phil[N] = {0, 1, 2, 3, 4};

HANDLE mutex;
HANDLE S[N];

void test(int i) {
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        Sleep(2000);
        printf("Philosopher %d takes forks %d and %d\n", i + 1, LEFT + 1, i + 1);
        printf("Philosopher %d is Eating\n", i + 1);
        ReleaseSemaphore(S[i], 1, NULL);
    }
}

void take_fork(int i) {
    WaitForSingleObject(mutex, INFINITE);
    state[i] = HUNGRY;
    printf("Philosopher %d is Hungry\n", i + 1);
    test(i);
    ReleaseMutex(mutex);
    WaitForSingleObject(S[i], INFINITE);
    Sleep(1000);
}

void put_fork(int i) {
    WaitForSingleObject(mutex, INFINITE);
    state[i] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", i + 1, LEFT + 1, i + 1);
    printf("Philosopher %d is thinking\n", i + 1);
    test(LEFT);
    test(RIGHT);
    ReleaseMutex(mutex);
}

DWORD WINAPI philosopher(void* num) {
    while (1) {
        int* i = num;
        Sleep(1000);
        take_fork(*i);
        Sleep(0);
        put_fork(*i);
    }
}

int main() {
    int i;
    HANDLE thread_id[N];

    mutex = CreateMutex(NULL, FALSE, NULL);
    for (i = 0; i < N; i++) {
        S[i] = CreateSemaphore(NULL, 0, 1, NULL);
    }

    for (i = 0; i < N; i++) {
        thread_id[i] = CreateThread(NULL, 0, philosopher, &phil[i], 0, NULL);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    WaitForMultipleObjects(N, thread_id, TRUE, INFINITE);

    for (i = 0; i < N; i++) {
        CloseHandle(thread_id[i]);
    }

    CloseHandle(mutex);
    for (i = 0; i < N; i++) {
        CloseHandle(S[i]);
    }

    return 0;
}
