#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#define FIFO_NAME1 "comm_pipe1"
#define FIFO_NAME2 "comm_pipe2"

int main()
{
    char s[300], vowel[20], send[50];
    int num, fd1, fd2, sig, k = 0, i, wordcnt = 1, charcnt = 0, linecnt = 0;

    mknod(FIFO_NAME1, S_IFIFO | 0666, 0);
    mknod(FIFO_NAME2, S_IFIFO | 0666, 0);
    printf("Waiting for producer...\n");
    fd1 = open(FIFO_NAME1, O_RDONLY);
    fd2 = open(FIFO_NAME2, O_WRONLY);
    printf("Got a producer\n");

    if ((num = read(fd1, s, 300)) == -1)
        perror("read");

    else
    {
        s[num] = '\0';
        printf("Tick: read %d bytes: \"%s\"\n", num, s);
        k = 0;
        vowel[0] = '\0';
        wordcnt = 1;
        for (i = 0; i < num; i++)
        {
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
            {
                vowel[k] = s[i];
                k++;
            }
            if (s[i] == ' ' && s[i + 1] != ' ')
            {
                wordcnt++;
            }
            if (s[i] == '.' && (s[i + 1] == ' ' || s[i + 1] == '\0'))
                linecnt++;
            else if (s[i] != '.' && s[i] != ' ')
                charcnt++;
        }
        vowel[k] = '\0';
        sprintf(send, "for the given sentence the word count is %d\n vowel count is %d\n character count is %d\n lines are %d\n", wordcnt, k, charcnt, linecnt);

        if (sig = write(fd2, send, strlen(send)) != -1)
            printf("\nWritten successfully to file2");
        else
            printf("\nError in writing to file2");
    }

    return 0;
}
