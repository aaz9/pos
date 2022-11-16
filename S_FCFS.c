#include <stdio.h>
#include <stdlib.h>
// structure to store data;
struct data
{
    int id;
    int at;
    int bt;
    int str_t;
    int end_t;
    int tat;
    int wai_t;
};
// function to take input;
void input()
{
    // variable declaration
    int n;
    printf(" Total number of process in the system: ");
    scanf("%d", &n);
    // structure memory allocation
    struct data *p = (struct data *)malloc(n * sizeof(struct data));
    for (int i = 0; i < n; i++)
    {
        int a, b;
        printf("Enter Arrival time and Burst time for process %d \n", i + 1);
        scanf("%d %d", &a, &b);
        p[i].id = i + 1;
        p[i].at = a;
        p[i].bt = b;
    }
    // sorting on basis of arrival time
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                struct data temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    int time = 0, i = 0, count = 0;
    float avg_wt, avg_tat;
    while (count != n)
    {
        if (p[i].at <= time)
        {
            p[i].str_t = time;
            p[i].end_t = time + p[i].bt;
            time = p[i].end_t;
            i++;
            count++;
        }
        else
            time++;
    }
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].end_t - p[i].at;
        p[i].wai_t = p[i].tat - p[i].bt;
    }
    printf("\npro_id\t arri_t\t bu_t\t str_t\t end_t\t tat\t wai_t\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t %d\t %d\t %d\t %d\t %d\t %d\n", p[i].id, p[i].at, p[i].bt, p[i].str_t, p[i].end_t, p[i].tat, p[i].wai_t);
    }
}
// main function;
int main()
{
    input();
    return 0;
}