#include<stdio.h>
void fcfs(int n,int bt[]);

void main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    int bt[n];
    printf("Enter the burst time: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&bt[i]);
    }
    printf("FCFS\n");
    fcfs(n,bt);
}

void fcfs(int n,int bt[])
{

    int wt[n],tat[n];
    int totalwt=0;
    int totaltat=0;
    wt[0]=0;

    for(int i=1;i<n;i++)
    {

        wt[i]=wt[i-1]+bt[i-1];

    }
    for(int i=0;i<n;i++)
    {

        tat[i]=wt[i]+bt[i];
        totalwt+=wt[i];
        totaltat+=tat[i];
    }
    printf("Average waiting time is %2f\n",(float)totalwt/n);
    printf("Average turn around time is %2f\n",(float)totaltat/n);
    printf("Name: Harsha Vardhan\nUSN: 1BM23CS136");
}
