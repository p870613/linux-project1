#include <linux/kernel.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <wait.h>//wait function
#include <string.h>

#define  MEMORY_SIZE  100000


int main()
{  
	int result_1[MEMORY_SIZE];
	int result_2[MEMORY_SIZE];
	int result_3[MEMORY_SIZE];
	int exit_status;


	if(fork())
	{   //executed by the parent process

		syscall(334,result_1);      //location 1
		wait(&exit_status);

		FILE *fpWrite1=fopen("result_1.txt","w");
		fprintf(fpWrite1,"%s",result_1);
		fclose(fpWrite1); 
	} 
	else
	{   //executed by the child process
		

		syscall(334,result_2);        //location 2

		result_1[0]=123;               //This should trigger copy-on-right, if the above system call does not trigger the COW.

		syscall(334,result_3);         //location 3

		FILE *fpWrite2=fopen("result_2.txt","w");
		fprintf(fpWrite2,"%s",result_2);
		fclose(fpWrite2); 
	
		FILE *fpWrite3=fopen("result_3.txt","w");
		fprintf(fpWrite3,"%s",result_3);
		fclose(fpWrite3); 
	}	
	return 0;
}  
