#include<stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<string.h>
int main()
{
	
	int in,i ;

	key_t key = 6000;
	//Obtaining Access to shared memory
	int shmid = shmget(key, 27, IPC_CREAT | 0666);
	if(shmid<0)
	{
		perror("Writer Error: Access Problem");
		return 0;
	}
 
	//Attaching the shared memory
	 char *shm = shmat(shmid, NULL, 0); 
        
	if(shm=="-1")
	{
		perror("Writer Error: Problem in attaching");
	        return 0;
	}

	


	//Inserting str into the shared memory..!!
	
	char str[100] = "INPUT";
	char *s = shm;
	printf("\nWriter Wrote: ");
	for (i=0;i<strlen(str);i++)
	{
		char c = str[i];	
		putchar(c);	
		*s++ = c;
	
    	}
	*s = '\0';
	
	
	
	printf("\nWRITER SLEEPING\n");
	while (*shm!= '*')
        	sleep(1);
	
	//Reading what reader inserted into the shared memory...!!
	printf("\nWriter Read:");	
	for (s = shm+1; *s!= '\0'; s++)
        	putchar(*s);
    	putchar('\n');


	return 0;

}
