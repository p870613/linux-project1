#include <linux/kernel.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <wait.h>//wait function
#include <string.h>

#define  MEMORY_SIZE  100000	//not 1000000 since it's too big that trigs segmentation fault
#define  linux_survey_TT(result) syscall(334,result)  // in syscall_64.tbl the linux_survey_TT is defined to syscall NO.334


int main()
{  
	int result_1[MEMORY_SIZE];	//acording to the project website, we use int array not char array
	int result_2[MEMORY_SIZE];
	int result_3[MEMORY_SIZE];

	int exit_status;


	if(fork())
	{   //executed by the parent process


		linux_survey_TT(result_1);      //location 1
		wait(&exit_status);

		//Save result_1 to txt
		FILE *fpWrite1=fopen("result_1.txt","w");
		fprintf(fpWrite1,"%s",result_1);
		fclose(fpWrite1); 


	} 
	else
	{   //executed by the child process
		

		linux_survey_TT(result_2);     //location 2

		result_1[0]=123;               //This should trigger copy-on-right, if the above system call does not trigger the COW.

		linux_survey_TT(result_3);     //location 3

		//Save result_2 to txt
		FILE *fpWrite2=fopen("result_2.txt","w");
		fprintf(fpWrite2,"%s",result_2);
		fclose(fpWrite2); 
		
		//Save result_3 to txt
		FILE *fpWrite3=fopen("result_3.txt","w");
		fprintf(fpWrite3,"%s",result_3);
		fclose(fpWrite3); 

	}
	
	return 0;
}  
