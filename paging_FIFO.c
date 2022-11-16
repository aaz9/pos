#include <stdio.h>

int check(int arr[], int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            return 1;
        }
    }
    return 0;
}

void print(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != 0)
        {
            printf("%d ", arr[i]);
        }
    }
}

void fifo(int arr[], int m, int page_frame[], int n)
{
    int fin = 0, page_fault = 0;
    for (int i = 0; i < m; i++)
    {
        if (check(page_frame, n, arr[i]))
        {
            printf("%d NPF ", arr[i]);
            print(page_frame, n);
            printf("\n");
            continue;
        }
        page_frame[fin] = arr[i];
        page_fault++;
        fin = (fin + 1) % n;
        printf("%d PF  ", arr[i]);
        print(page_frame, n);
        printf("\n");
    }
    printf("Page faults: %d\n", page_fault);
}

int main()
{
    int n;
    printf("Enter number of page frames: ");
    scanf("%d", &n);

    int page_frame[n];
    for (int i = 0; i < n; i++)
    {
        page_frame[i] = 0;
    }

    int m;
    printf("Enter number of pages : ");
    scanf("%d", &m);
    int arr[m];
    printf("Enter pages : \n");
    for (int i = 0; i < m; i++)
    {
        printf("Page No %d : ", i + 1);
        scanf("%d", &arr[i]);
    }

    fifo(arr, m, page_frame, n);
    return 0;
}
