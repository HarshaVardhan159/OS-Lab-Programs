#include<stdio.h>
#include<stdlib.h>
#define BUFFER_SIZE 5

void wait(int *mutex){
    --(*mutex);
}

void signal(int *mutex){
    ++(*mutex);
}

void producer(int *x, int *mutex, int *full, int *empty){
    if (*empty > 0){
        wait(mutex);
        (*x)++;
        (*full)++;
        (*empty)--;
        printf("Producer has produced Item %d\n", *x);
        signal(mutex);
    }
    else{
        printf("Buffer is full\n");
    }
}

void consumer(int *x, int *mutex, int *full, int *empty){
    if (*full > 0){
        wait(mutex);
        printf("Consumer has consumed: Item %d\n", *x);
        (*x)--;
        (*full)--;
        (*empty)++;
        signal(mutex);
    }
    else{
        printf("Buffer is empty\n");
    }
}

int main(){
    int x = 0;
    int mutex = 1, full = 0, empty = BUFFER_SIZE;
    int choice;
    while(1){
        printf("\nEnter 1.Produce 2.Consume 3.Exit\n");
        scanf("%d", &choice);
        switch(choice){
        case 1:
            producer(&x, &mutex, &full, &empty);
            break;
        case 2:
            consumer(&x, &mutex, &full, &empty);
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice\n");
            break;
        }
    }
    return 0;
}
