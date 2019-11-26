#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main()
{   
    int test[10000000];
    syscall(548, test);
    return 0;
}