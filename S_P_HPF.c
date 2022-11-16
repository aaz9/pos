#include <stdio.h>
#include <stdlib.h>
struct process
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int start_time;
    int end_time;
    int tot;
    int waiting_time;
    int remain_time;
};
void input(int n)
{
    struct process *p = (struct process *)malloc(n * sizeof(struct process));

    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        printf("Enter arrival_t, Burst_t and Priority for process %d : ", i + 1);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].remain_time = p[i].burst_time;
    }

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
    int count = 0;
    int i;
    int current = -1;
    int time = 0;
    while (count != n)
    {
        for (i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= time)
            {
                if (p[i].remain_time > 0)
                {
                    if (current == -1)
                        current = i;
                    else if (p[i].priority < p[current].priority)
                        current = i;
                }
            }
            else
                break;
        }
        if (current == -1)
            time++;
        else
        {
            if (p[current].remain_time == p[current].burst_time)
            {
                p[current].start_time = time;
                // p[current].end_time=time+p[current].burst_time;
                p[current].remain_time--;
                time++;
                if (p[current].remain_time == 0)
                {
                    p[current].end_time = time;
                    count++;
                }
                current = -1;
            }
            else
            {
                p[current].remain_time--;
                time++;
                if (p[current].remain_time == 0)
                {
                    p[current].end_time = time;
                    count++;
                }
                current = -1;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        p[i].tot = p[i].end_time - p[i].arrival_time;
        p[i].waiting_time = p[i].tot - p[i].burst_time;
    }

    printf("ID\tAT\tBT\tPRI\tST\tET\tTOT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n", p[i].id, p[i].arrival_time, p[i].burst_time, p[i].priority, p[i].start_time, p[i].end_time, p[i].tot, p[i].waiting_time);
    }
}
int main()
{
    int n;
    printf("Enter no of procesess : ");
    scanf("%d", &n);
    input(n);
}