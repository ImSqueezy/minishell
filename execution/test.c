#include "../execution.h"

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    else if(pid == 0)
        printf("the pid of child process is = %d\n", getpid());
    else
        printf("the pid of the parent process is = %d , and child's process is = %d\n", getpid(), pid);
    return 0;
}