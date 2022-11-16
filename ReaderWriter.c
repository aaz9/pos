#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define R 5
#define W 5
int readcount;
pthread_mutex_t x;
sem_t wsem; // mutual exclusion
int s = 5;
void *reader1(void *a);
void *writer1(void *a);

int main()
{
    int i;

    pthread_t thread_read[R], thread_write[W];
    pthread_mutex_init(&x, NULL); // initializeed to default value
    sem_init(&wsem, 0, 1);

    readcount = 0;
    for (i = 0; i < W; i++)
    {
        pthread_create(&thread_write[i], NULL, *writer1, (void *)i);
    }
    for (i = 0; i < R; i++)
    {
        pthread_create(&thread_read[i], NULL, *reader1, (void *)i);
    }
    for (i = 0; i < W; i++)
    {
        pthread_join(thread_write[i], NULL);
    }
    for (i = 0; i < R; i++)
    {
        pthread_join(thread_read[i], NULL);
    }
}

void *reader1(void *a)
{
    int r = (int)a;
    int i = 0;
    while (i < 5)
    {
        pthread_mutex_lock(&x);
        readcount++;
        if (readcount == 1)
            sem_wait(&wsem);

        pthread_mutex_unlock(&x);
        printf("\t\tReader %d is reading : %d \n", r, s);
        // sem_wait(&x);
        pthread_mutex_lock(&x);
        readcount--;
        if (readcount == 0)
            sem_post(&wsem);

        pthread_mutex_unlock(&x);
        sleep(rand() % 10);
        i++;
    }
}

void *writer1(void *a)
{
    int w = (int)a;
    int i = 0;
    while (i < 2)
    {
        sem_wait(&wsem);
        s += 5;
        printf("Writer %d is writing : %d \n", w, s);
        sem_post(&wsem);
        sleep(rand() % 10);
        i++;
    }
}