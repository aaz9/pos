#include <stdio.h>
#include <stdlib.h>
struct frame
{
    int id;
    int index;
};
int check(struct frame *arr, int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i].id == key)
        {
            arr[i].index = i;
            return 1;
        }
    }
    return 0;
}

void print(struct frame *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i].id != 0)
            printf("%d ", arr[i].id);
    }
}

void lru(int arr[], int m, struct frame *pframe, int n)
{
    int fin = 0, pfault = 0;
    for (int i = 0; i < m; i++)
    {
        if (check(pframe, n, arr[i]))
        {
            printf("%d NPF ", arr[i]);
            print(pframe, n);
            printf("\n");
            continue;
        }
        fin = 0;
        for (int j = 1; j < n; j++)
        {
            if (pframe[j].index < pframe[fin].index)
                fin = j;
        }
        pframe[fin].id = arr[i];
        pframe[fin].index = i;
        pfault++;
        // fin = (fin + 1) % n;
        printf("%d PF  ", arr[i]);
        print(pframe, n);
        printf("\n");
    }
    printf("Page faults: %d\n", pfault);
}

int main()
{
    int n;
    printf("Enter number of page frames: ");
    scanf("%d", &n);
    struct frame *pframe = (struct frame *)malloc(n * sizeof(struct frame));
    for (int i = 0; i < n; i++)
    {
        pframe[i].id = 0;
        pframe[i].index = -1;
    }
    int m;
    printf("Enter number of pages: ");
    scanf("%d", &m);
    int arr[m];
    printf("Enter pages: ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &arr[i]);
    }
    lru(arr, m, pframe, n);
    return 0;
}