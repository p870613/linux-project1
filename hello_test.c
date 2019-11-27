#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main()
{   
    char t[1000] ;
    syscall(548, t);

    return 0;
}