#include <stdio.h>
#include <stdlib.h>
// structure to store data;
struct process
{
    int id;
    int arrival_time;
    int burst_time;
    int start_time;
    int end_time;
    int tot;
    int waiting_time;
    int remain_time;
};
// function to take input;
void input()
{
    // variable declaration
    int n, tq;
    printf(" Total number of process in the system: ");
    scanf("%d", &n);
    // structure memory allocation
    struct process *p = (struct process *)malloc(n * sizeof(struct process));
    printf(" Enter Time Quantum : ");
    scanf("%d", &tq);
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        printf("Enter arrival_t and Burst_t for process %d : ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].remain_time = p[i].burst_time;
    }
    // sorting on basis of arrival time
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].arrival_time > p[j].arrival_time)
            {
                struct process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    int time = 0, i = 0, count = 0;
    float avg_wt, avg_tat;
    while (count != n)
    {
        if (p[i].arrival_time <= time)
        {
            if (p[i].remain_time > 0)
            {
                if (p[i].burst_time == p[i].remain_time)
                {
                    p[i].start_time = time;
                    int t = p[i].remain_time <= tq ? 0 : (p[i].remain_time - tq);
                    if (t)
                    {
                        p[i].remain_time -= tq;
                        time += tq;
                        i++;
                    }
                    else
                    {
                        p[i].end_time = time + p[i].remain_time;
                        time += p[i].remain_time;
                        p[i].remain_time = 0;
                        count++;
                        i++;
                    }
                }
                else
                {
                    int t = p[i].remain_time <= tq ? 0 : (p[i].remain_time - tq);
                    if (t)
                    {
                        p[i].remain_time -= tq;
                        time += tq;
                        i++;
                    }
                    else
                    {
                        p[i].end_time = time + p[i].remain_time;
                        time += p[i].remain_time;
                        p[i].remain_time = 0;
                        count++;
                        i++;
                    }
                }
                // p[i].start_time = time;
                // p[i].end_t = time + p[i].bt;
                // time = p[i].end_t;
                // i++;
                // count++;
            }
            else
                i++;

            if (i == n)
                i = 0;
        }
        else
            time++;
    }

    for (int i = 0; i < n; i++)
    {
        p[i].tot = p[i].end_time - p[i].arrival_time;
        p[i].waiting_time = p[i].tot - p[i].burst_time;
    }

    printf("ID\tAT\tBT\tST\tET\tTOT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t %d\t %d\t %d\t %d\t %d\t %d\n", p[i].id, p[i].arrival_time, p[i].burst_time, p[i].start_time, p[i].end_time, p[i].tot, p[i].waiting_time);
    }
}
// main function;
int main()
{
    input();
    return 0;
}